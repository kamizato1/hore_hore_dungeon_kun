#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Player.h"

#define PLAYER_SIZE_X 30.0f
#define PLAYER_SIZE_Y 30.0f
#define JUMP_SPEED 8.0f
#define PLAYER_SPEED 2.0f
#define ITEM_ANGLE 30
#define ITEM_SET_TIME 10

Player::Player()
{
    Init();
    for (int i = 0; i < ITEM_TYPE_NUM; i++)item_num[i] = 0;
    for(int i = 0; i < TREASURE_TYPE_NUM; i++)treasure_num[i] = 0;
    LoadDivGraph("images/Player/player1.png", 5, 5, 1, 30, 30, image);
    LoadDivGraph("images/Player/marubatu1.png", 2, 2, 1, 20, 20, answer_image);
    LoadDivGraph("images/Player/item.png", ITEM_TYPE_NUM, ITEM_TYPE_NUM, 1, 50, 50, item_image);
    break_block_num = 0;
}

void Player::Init()
{
    location = { 50, 669 };
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
    clear = FALSE;
}

void Player::Update(Key* key, Stage* stage)
{
   if (location.y > SCREEN_HEIGHT + 50)die = TRUE;

   if(!die)
   {
       if (stage->HitFlag(this))clear = TRUE;
    
       MoveX(key, stage);
       MoveY(key, stage);

       //ここから下↓つるはしを投げるときの処理
       DATA all_r_stick_angle_record_calculation = { 0,0 };
       DATA now_r_stick_angle, old_r_stick_angle;
       now_r_stick_angle.x = (key->GetStickAngle(R).y / 50);//照準を変えるときはここを変えてね
       now_r_stick_angle.y = (key->GetStickAngle(R).x / 50);//照準を変えるときはここを変えてね

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

       if (--item_set_time < 0)item_set_time = 0;

       if ((item_set_time == 0) && (!clear))
       {
           if (key->KeyDown(L))
           {
               if (can_throw)
               {
                   if (stage->ThrowItem(location, throw_speed, static_cast<ITEM_TYPE>(item_type), item_num[item_type]))
                   {
                       item_num[item_type]--;
                       item_set_time = ITEM_SET_TIME;
                   }
               }
           }
           else if (key->KeyDown(R))
           {
               if (stage->PutItem(cursor, static_cast<ITEM_TYPE>(item_type), item_num[item_type]))
               {
                   if (item_type == 0)break_block_num++;
                   else
                   {
                       item_num[item_type]--;
                       item_set_time = ITEM_SET_TIME;
                   }
               }
               if (item_type == 0)item_set_time = ITEM_SET_TIME;
           }
       }

       pickaxe_flg = stage->GetPickaxeFlg();

       break_block_num += stage->GetBreakBlockNum();
       if (break_block_num >= 50)
       {
           item_num[1] += (break_block_num / 50);
           break_block_num -= (break_block_num / 50) * 50;
       }

       treasure_num[0] = item_num[1];//アイテムのブロックを宝のブロックに代入
       HIT_TREASURE hit_treasure = stage->HitTreasure(this);
       if (hit_treasure.flg)
       {
           stage->DeleteTreasure(hit_treasure.num);
           if (hit_treasure.treasure_type == TREASURE_TYPE::BOM)item_num[static_cast<int>(ITEM_TYPE::BOM)]++;
           else treasure_num[static_cast<int>(hit_treasure.treasure_type)]++;
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
    if (clear)now_speed_x = PLAYER_SPEED;

    for (int i = 0; i < L_STICK_ANGLE_RECORD_NUM; i++)
    {
        old_speed_x = speed_x_record[i];
        speed_x_record[i] = now_speed_x;
        now_speed_x = old_speed_x;
        all_speed_x_record_calculation += speed_x_record[i];
    }
    float l_stick_angle_record_num = static_cast<float>(L_STICK_ANGLE_RECORD_NUM);
    speed.x = (all_speed_x_record_calculation / l_stick_angle_record_num);
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
            if(image_type == 4)image_type = 0;
        }
    }
    else image_type = 4;
}

void Player::Draw(float camera_work) const
{
    if (can_throw)
    {
        float throw_speed_y = throw_speed.y;
        DATA throw_location = location;
        int count = 0;
        while (throw_location.y < SCREEN_HEIGHT)
        {
            throw_speed_y += GRAVITY_POWER;
            throw_location.y += throw_speed_y;
            throw_location.x += throw_speed.x;
            if ((++count % 5) == 0) DrawRotaGraph(throw_location.x + camera_work, throw_location.y, 1, 0, answer_image[0], TRUE);
        }
    }
    cursor->Draw(camera_work);
    DrawRotaGraph(location.x + camera_work, location.y, 1, 0, image[image_type], TRUE, direction);

    if (item_type == 0)
    {
        int angle = (direction * 30) + ((item_set_time * 10) * -direction);
        if (pickaxe_flg)DrawRotaGraph(location.x + camera_work + (direction * 4), location.y, 1, (M_PI / 180) * angle, item_image[item_type], TRUE);
    }
    else if ((item_set_time == 0) && (item_num[item_type] != 0))
    {
        DrawRotaGraph(location.x + camera_work + (direction * 13), location.y, 0.6, (0.3 * direction), item_image[item_type], TRUE);
    }

    if (item_type == 1)DrawString(0, 60, "ブロック", 0xffffff);
    else if(item_type == 2)DrawString(0, 60, "爆弾", 0xffffff);
    else DrawString(0, 60, "つるはし", 0xffffff);
    DrawFormatString(0, 100, 0xffffff, "%d", item_num[item_type]);
    DrawFormatString(0, 160, 0xffffff, "%d",break_block_num);
    DrawFormatString(0, 190, 0xffffff, "%d, %d, %d, %d, %d", treasure_num[0], treasure_num[1], treasure_num[2], treasure_num[3], treasure_num[4]);
}
