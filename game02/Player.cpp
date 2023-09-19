#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Player.h"

#define PLAYER_SIZE_X 30.0f
#define PLAYER_SIZE_Y 30.0f
#define JUMP_SPEED 8.0f
#define PLAYER_SPEED 2.0f
#define ITEM_ANGLE 30

Player::Player()
{
    Init();
    for(int i = 0; i < TREASURE_TYPE_NUM; i++)treasure_num[i] = 0;

    int count = 0;
    LoadDivGraph("images/Player/player.png", 10, 5, 2, 30, 30, set_image);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)this->image[i][j] = set_image[count++];
    }
    LoadDivGraph("images/Player/item.png", ITEM_TYPE_NUM, ITEM_TYPE_NUM, 1, 50, 50, item_image);
    frame_image = LoadGraph("images/Player/frame.png");
    sign_image = LoadGraph("images/Player/sign.png");
    jump_se = LoadSoundMem("bgm/JumpSE.mp3");
    get_treasure_se = LoadSoundMem("bgm/GetItem.mp3");
    die_se = LoadSoundMem("bgm/playerdie.mp3");
    select_se = LoadSoundMem("bgm/MoveCursor.mp3");

    break_block_num = 0;
}

void Player::Delete()
{
    for (int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 5; j++)DeleteGraph(image[i][j]);
    }
    for (int i = 0; i < ITEM_TYPE_NUM; i++)DeleteGraph(item_image[i]);
    for (int i = 0; i < 10; i++)DeleteGraph(set_image[i]);
    DeleteGraph(sign_image);
    DeleteGraph(frame_image);

    DeleteSoundMem(jump_se);
    DeleteSoundMem(get_treasure_se);
    DeleteSoundMem(die_se);
    DeleteSoundMem(select_se);

    cursor->Delete();
    delete cursor;
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
    pickaxe_flg = TRUE;
    clear = FALSE;
    for (int i = 0; i < ITEM_TYPE_NUM; i++)
    {
        now_item_set_time[i] = item_set_time[i];
        can_use_item[i] = FALSE;
    }
}

void Player::Update(Key* key, Stage* stage)
{
    if (location.y > SCREEN_HEIGHT + 50)
    {
        if(!die)PlaySoundMem(die_se, DX_PLAYTYPE_BACK, TRUE);
        die = TRUE;
    }

   if(!die)
   {
       if (stage->HitFlag(this))clear = TRUE;
    
       if (++image_change_time > 10)
       {
           if (++image_type > 3)image_type = 0;
           image_change_time = 0;
       }

       MoveX(key, stage);
       MoveY(key, stage);

       //ここから下↓つるはしを投げるときの処理
       DATA all_r_stick_angle_record_calculation = { 0,0 };
       DATA now_r_stick_angle, old_r_stick_angle;
       now_r_stick_angle.x = (key->GetStickAngle(R).y / 50);//照準を変えるときはここを変えてね
       now_r_stick_angle.y = (key->GetStickAngle(R).x/ 50);//照準を変えるときはここを変えてね

       for (int i = 0; i < R_STICK_ANGLE_RECORD_NUM; i++)
       {
           old_r_stick_angle = r_stick_angle_record[i];
           r_stick_angle_record[i] = now_r_stick_angle;
           now_r_stick_angle = old_r_stick_angle;
           all_r_stick_angle_record_calculation.x += r_stick_angle_record[i].x;//ここを変えるんじゃねぇ
           all_r_stick_angle_record_calculation.y += r_stick_angle_record[i].y;//ここを変えるんじゃねぇ
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
               if (++item_type == ITEM_TYPE_NUM)item_type = 0;
               PlaySoundMem(select_se, DX_PLAYTYPE_BACK, TRUE);
           }
           else if (key->KeyDown(LEFT))
           {
               if (--item_type == -1)item_type = ITEM_TYPE_NUM - 1;
               PlaySoundMem(select_se, DX_PLAYTYPE_BACK, TRUE);
           }
       }


       for (int i = 0; i < ITEM_TYPE_NUM; i++)if (++now_item_set_time[i] > item_set_time[i])now_item_set_time[i] = item_set_time[i];
       
       if (!clear)
       {
           if (key->KeyDown(L))
           {
               if ((can_throw) && (can_use_item[item_type]))
               {
                   stage->ThrowItem(location, throw_speed, static_cast<ITEM_TYPE>(item_type));
                   if (item_type == 2)now_item_set_time[2] = 0;
               }
           }
           else if (key->KeyDown(R))
           {
               if (can_use_item[item_type])
               {
                   if (stage->PutItem(cursor, static_cast<ITEM_TYPE>(item_type)))
                   {
                       if (item_type == 0)break_block_num++;
                       else now_item_set_time[item_type] = 0;
                   }
                   if (item_type == 0)now_item_set_time[0] = 0;
               }
           }
       }

       pickaxe_flg = stage->GetPickaxeFlg();

       break_block_num += stage->GetBreakBlockNum();
       if (break_block_num >= 50)
       {
           treasure_num[0] += (break_block_num / 50);
           break_block_num -= (break_block_num / 50) * 50;
           if (treasure_num[0] >= 100)treasure_num[0] = 99;
       }

       HIT_TREASURE hit_treasure = stage->HitTreasure(this, FALSE);
       if (hit_treasure.flg)
       {
           int treasure_type = static_cast<int>(hit_treasure.treasure_type);
           stage->DeleteTreasure(hit_treasure.num);
           if (++treasure_num[treasure_type] >= 100)treasure_num[treasure_type] = 99;
           PlaySoundMem(get_treasure_se, DX_PLAYTYPE_BACK, TRUE);
       }

       for (int i = 0; i < ITEM_TYPE_NUM; i++)can_use_item[i] = FALSE;
       if (pickaxe_flg)can_use_item[0] = TRUE;
       if (now_item_set_time[1] == item_set_time[1])can_use_item[1] = TRUE;
       if (now_item_set_time[2] == item_set_time[2])can_use_item[2] = TRUE;
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
    speed.x = static_cast<float>((all_speed_x_record_calculation / L_STICK_ANGLE_RECORD_NUM));
    location.x += speed.x;

    if (speed.x != 0)
    {
        if (speed.x > 0)direction = -1;
        else direction = 1;
    }

    if (stagebase->HitBlock(this).flg)
    {
        location.x = floorf(location.x);
        while (stagebase->HitBlock(this).flg)location.x += static_cast<float>(direction);
    }
}

void Player::MoveY(Key* key, Stage* stagebase)//Ｙ座標の移動
{
    if ((speed.y += GRAVITY_POWER) > MAX_FALL_SPEED )speed.y = MAX_FALL_SPEED;//重力の大きさが一定に達すまでスピードに重力を足し続けて下に落とす。
    location.y += speed.y;//スピードをY座標に足す。

    if (stagebase->HitBlock(this).flg)//ステージにぶつかっていたら、
    {
        location.y = floorf(location.y);
        float sign = -(speed.y / fabsf(speed.y));
        while (stagebase->HitBlock(this).flg)location.y += sign;

        speed.y = 0;

        if (sign == -1)//地面に触れているとき
        {
            if (key->KeyDown(A))
            {
                speed.y = -JUMP_SPEED;
                PlaySoundMem(jump_se, DX_PLAYTYPE_BACK, TRUE);
            }
            if(image_type == 4)image_type = 0;
        }
    }
    else image_type = 4;
}

void Player::Draw(float camera_work) const
{
    if ((!die) && (!clear))
    {
        if ((can_throw) && (item_type != 1))
        {
            float throw_speed_y = throw_speed.y;
            DATA throw_location = location;
            int count = 0;
            while (throw_location.y < SCREEN_HEIGHT)
            {
                throw_speed_y += GRAVITY_POWER;
                throw_location.y += throw_speed_y;
                throw_location.x += throw_speed.x;
                if ((++count % 5) == 0) DrawRotaGraph(throw_location.x + camera_work, throw_location.y, 1, 0, sign_image, TRUE);
            }
        }
        cursor->Draw(camera_work);
    }

    int player_image_type = 0;
    if ((speed.x == 0) && (speed.y == 0))player_image_type = 1;

    DrawRotaGraph(location.x + camera_work, location.y, 1, 0, image[player_image_type][image_type], TRUE, direction);

    if (item_type == 0)
    {
        int angle = (50 * -direction) + ((now_item_set_time[0] * 10) * direction);
        if (pickaxe_flg)DrawRotaGraph(location.x + camera_work + (direction * 4), location.y + (player_image_type * image_type), 1, (M_PI / 180) * angle, item_image[item_type], TRUE);
    }
    else if (can_use_item[item_type])
    {
        DrawRotaGraph(location.x + camera_work + (direction * 14), location.y + (player_image_type * image_type), 1, (0.3 * direction), item_image[item_type], TRUE);
        if ((!die) && (!clear) && (item_type == 2))DrawRotaGraph(cursor->GetLocation().x + camera_work, cursor->GetLocation().y, 1, 0, frame_image, TRUE);
    }
}

PLAYER_UI Player::GetPlayerUi()const
{
    PLAYER_UI player_ui;
    player_ui.item_type = item_type;
    for (int i = 0; i < ITEM_TYPE_NUM; i++)
    {
        player_ui.now_item_set_time[i] = now_item_set_time[i];
        player_ui.item_set_time[i] = item_set_time[i];
    }
    for (int i = 0; i < TREASURE_TYPE_NUM; i++)player_ui.treasure_num[i] = treasure_num[i];
    player_ui.break_block_num = break_block_num;
    return player_ui;
}


