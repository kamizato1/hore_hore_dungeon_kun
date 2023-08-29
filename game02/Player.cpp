#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Player.h"

#define PLAYER_SIZE_X 30
#define PLAYER_SIZE_Y 30
#define JUMP_SPEED 8
#define PLAYER_SPEED 2
#define ITEM_ANGLE 30
#define ITEM_SET_TIME 10

Player::Player()
{
    Init();
    for (int i = 0; i < 3; i++)item_num[i] = 999;
    LoadDivGraph("images/player.png", 4, 4, 1, 30, 30, image);
    LoadDivGraph("images/marubatu1.png", 2, 2, 1, 20, 20, answer_image);
    item_image[0] = LoadGraph("images/tsuruhashi.png");
    item_image[1] = LoadGraph("images/angrybom.png");
    item_image[2] = LoadGraph("images/angrybom.png");
}

void Player::Init()
{

    location = { 55, 500 };
    radius = { PLAYER_SIZE_X / 2, PLAYER_SIZE_Y / 2 };
    speed = { 0,0 };
    throw_speed = { 0,0 };
    item_type = static_cast<int>(ITEM_TYPE::PICKAXE);
    can_throw = FALSE;
    die = FALSE;
    for (int i = 0; i < R_STICK_ANGLE_RECORD_NUM; i++)r_stick_angle_record[i] = { 0,0 };
    for (int i = 0; i < L_STICK_ANGLE_RECORD_NUM; i++)speed_x_record[i] = 0;
    cursor = new Cursor(location);
    direction = -1;
    image_type = 0;
    image_change_time = 0;
    item_set_time = 0;
    pickaxe_flg = TRUE;
}

void Player::Update(Key* key, Stage* stage)
{
   if (location.y > SCREEN_HEIGHT + 50)die = TRUE;

   if(!die)
   {
       MoveX(key, stage);
       MoveY(key, stage);

       HIT_TREASURE hit_treasure = stage->HitTreasure(this);

       if (hit_treasure.flg)
       {
           stage->DeleteTreasure(hit_treasure.num);
           item_num[static_cast<int>(hit_treasure.treasure_type)]++;
       }

       //ここから下↓つるはしを投げるときの処理

       DATA all_r_stick_angle_record_calculation = { 0,0 };
       DATA now_r_stick_angle, old_r_stick_angle;

       now_r_stick_angle.x = (key->GetStickAngle(R).y / 50);
       now_r_stick_angle.y = (key->GetStickAngle(R).x / 50);

       for (int i = 0; i < R_STICK_ANGLE_RECORD_NUM; i++)
       {
           old_r_stick_angle = r_stick_angle_record[i];
           r_stick_angle_record[i] = now_r_stick_angle;
           now_r_stick_angle = old_r_stick_angle;
           all_r_stick_angle_record_calculation.x += r_stick_angle_record[i].x;
           all_r_stick_angle_record_calculation.y += r_stick_angle_record[i].y;
       }

       throw_speed.x = (all_r_stick_angle_record_calculation.x / R_STICK_ANGLE_RECORD_NUM);
       throw_speed.y = (all_r_stick_angle_record_calculation.y / R_STICK_ANGLE_RECORD_NUM);

       if ((throw_speed.x == 0) && (throw_speed.y == 0))can_throw = FALSE;
       else can_throw = TRUE;

       cursor->Update(this, throw_speed);

       if (key->GetStickAngle(L).x == 0)
       {
           if (key->KeyDown(RIGHT))
           {
               if (++item_type == ITEM_TYPE_NUM)item_type = 0, item_set_time = 0;
           }
           else if (key->KeyDown(LEFT))
           {
               if (--item_type == -1)item_type = ITEM_TYPE_NUM - 1, item_set_time = 0;
           }
       }

       if (item_set_time != 0)
       {
           if (++item_set_time > ITEM_SET_TIME)item_set_time = 0;
       }

       pickaxe_flg = stage->GetPickaxeFlg();

       if (key->KeyDown(L))
       {
           if ((can_throw) && (item_set_time == 0))
           {
               if (stage->ThrowItem(location, throw_speed, static_cast<ITEM_TYPE>(item_type), item_num[item_type]))
               {
                   item_num[item_type]--;
                   item_set_time++;
               }
           }
       }
       else if (key->KeyDown(R))
       {
           if (item_set_time == 0)
           {
               if (stage->PutItem(cursor, static_cast<ITEM_TYPE>(item_type), item_num[item_type]))
               {
                   item_num[item_type]--;
                   item_set_time++;
               }
           }
       }
   }
}

void Player::MoveX(Key* key, Stage* stagebase)//Ｘ座標の移動
{
    float all_speed_x_record_calculation = 0;
    float now_speed_x = 0;
    float old_speed_x = 0;

    if (key->GetStickAngle(L).x > 0)now_speed_x = PLAYER_SPEED;
    else if (key->GetStickAngle(L).x < 0)now_speed_x = -PLAYER_SPEED;

    for (int i = 0; i < L_STICK_ANGLE_RECORD_NUM; i++)
    {
        old_speed_x = speed_x_record[i];
        speed_x_record[i] = now_speed_x;
        now_speed_x = old_speed_x;
        all_speed_x_record_calculation += speed_x_record[i];
    }

    speed.x = (all_speed_x_record_calculation / L_STICK_ANGLE_RECORD_NUM);

    location.x += speed.x;

    if (stagebase->HitBlock(this).flg)
    {
        location.x = floor(location.x);
        float sign = -(speed.x / fabsf(speed.x));
        while (stagebase->HitBlock(this).flg)location.x += sign;
    }
    else if (speed.x != 0)
    {
        if (++image_change_time > 10)
        {
            if (++image_type > 3)image_type = 0;
            image_change_time = 0;
        }
        if (speed.x > 0)direction = -1;
        else direction = 1;
    }

}

void Player::MoveY(Key* key, Stage* stagebase)//Ｙ座標の移動
{
    if ((speed.y += GRAVITY_POWER) > MAX_FALL_SPEED )speed.y = MAX_FALL_SPEED;//重力の大きさが一定に達すまでスピードに重力を足し続けて下に落とす。
    location.y += speed.y;//スピードをY座標に足す。

    if (stagebase->HitBlock(this).flg)//ステージにぶつかっていたら、
    {
        location.y = floor(location.y);
        float sign = -(speed.y / fabsf(speed.y));
        while (stagebase->HitBlock(this).flg)location.y += sign;

        speed.y = 0;

        if (sign == -1)//地面に触れているとき
        {
            if (key->KeyDown(A))speed.y = -JUMP_SPEED;
        }
    }
}

void Player::Draw(float camera_work) const
{
    if (can_throw)
    {
        int image_type = 0;
        if((item_type == 1) || (item_num[item_type] == 0) || (item_type == 0 && !pickaxe_flg))image_type = 1;
        float throw_speed_y = throw_speed.y;
        DATA throw_location = location;
        int count = 0;
        while (throw_location.y < SCREEN_HEIGHT)
        {
            throw_location.x += throw_speed.x;
            throw_speed_y += GRAVITY_POWER;
            throw_location.y += throw_speed_y;
                if (!(++count % 5))
                {
                    DrawRotaGraph(throw_location.x + camera_work, throw_location.y, 1, 0, answer_image[image_type], TRUE);
                    //DrawCircle(throw_location.x + camera_work, throw_location.y, 3, 0xffffff, FALSE);
                }
        }
    }

    cursor->Draw(camera_work);
    DrawRotaGraph(location.x + camera_work, location.y, 1, 0, image[image_type], TRUE, direction);
    if (item_type == 0)
    {
        if (pickaxe_flg)
        {
            int angle = (direction * 30) + ((item_set_time * 10) * -direction);
            DrawRotaGraph(location.x + camera_work + (direction * 5), location.y, 1, (M_PI / 180) * angle, item_image[item_type], TRUE);
        }
    }
    else if ((item_set_time == 0) && (item_num[item_type] != 0))
    {
        DrawRotaGraph(location.x + camera_work + (direction * 10), location.y, 0.8, 0, item_image[item_type], TRUE);
    }

    if (item_type == 1)DrawString(0, 60, "ブロック", 0xffffff);
    else if(item_type == 2)DrawString(0, 60, "爆弾", 0xffffff);
    else DrawString(0, 60, "つるはし", 0xffffff);
    DrawFormatString(0, 100, 0xffffff, "%d", item_num[item_type]);
}