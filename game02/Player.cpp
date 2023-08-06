#include"DxLib.h"
#include <math.h>
#include"Player.h"

#define PLAYER_SIZE_X 30
#define PLAYER_SIZE_Y 30

#define JUMP_SPEED 10
#define PLAYER_SPEED 2


Player::Player()
{
    location = { 10, 300 };
    radius = { PLAYER_SIZE_X / 2, PLAYER_SIZE_Y / 2 };
    speed = { 0,0 };
    throw_speed = { 0,0 };
   
    for (int i = 0; i < R_STICK_ANGLE_RECORD_NUM; i++)r_stick_angle_record[i] = { 0,0 };
    for (int i = 0; i < L_STICK_ANGLE_RECORD_NUM; i++)speed_x_record[i] = 0;

    cursor_image = LoadGraph("images/cursor.png");
    item_type = ITEM_TYPE::PICKAXE;
    can_use_item = FALSE;

    for (int i = 0; i < 3; i++)item_num[i] = 0;
}

void Player::Update(Key* key, Stage* stage)
{
    MoveX(key, stage);
    MoveY(key, stage);
    
    if (stage->HitTreasure(this, TRUE) == TREASURE_TYPE::BOM)
    {
        item_num[static_cast<int>(ITEM_TYPE::BOM)]++;
    }

    //ここから下↓つるはしを投げるときの処理

    DATA all_r_stick_angle_record_calculation = { 0,0 };
    DATA now_r_stick_angle, old_r_stick_angle;

    now_r_stick_angle.x = -(key->GetStickAngle(R).y / 50);
    now_r_stick_angle.y = -(key->GetStickAngle(R).x / 50);
    
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

    if ((throw_speed.x == 0) && (throw_speed.y == 0))can_use_item = FALSE;
    else can_use_item = TRUE;

    if(can_use_item)Cursor();

    if (speed.x == 0)
    {
        int item_type = static_cast<int>(this->item_type);
        if (key->KeyDown(RIGHT))
        {
            if (++item_type >= ITEM_TYPE_NUM)item_type = 0;
        }
        else if (key->KeyDown(LEFT))
        {
            if(--item_type < 0)item_type = ITEM_TYPE_NUM - 1;
        }
        this->item_type = static_cast<ITEM_TYPE>(item_type);
    }

    if (can_use_item)
    {
        if (key->KeyDown(L))stage->ThrowItem(location, throw_speed, item_type);
        else if (key->KeyDown(R))stage->PutItem(cursor_location, item_type);
    }
}

void Player::Cursor()
{
    int cursor_sign_x = 0;
    if (throw_speed.x != 0)cursor_sign_x = -(throw_speed.x / fabsf(throw_speed.x));
    int cursor_sign_y = 0;
    if (throw_speed.y != 0)cursor_sign_y = -(throw_speed.y / fabsf(throw_speed.y));

    DATA cursor_radius = { BLOCK_SIZE_X / 2, BLOCK_SIZE_Y / 2 };
    cursor_location.x = (floor(location.x / BLOCK_SIZE_X) * BLOCK_SIZE_X) + cursor_radius.x;
    cursor_location.y = (floor(location.y / BLOCK_SIZE_Y) * BLOCK_SIZE_Y) + cursor_radius.y;
    
    while (HitBox(this, cursor_location, cursor_radius))
    {
        cursor_location.x += (BLOCK_SIZE_X * cursor_sign_x);
        cursor_location.y += (BLOCK_SIZE_Y * cursor_sign_y);
    }
}

void Player::MoveX(Key* key, Stage* stage)//Ｘ座標の移動
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

    if (stage->HitStage(this))
    {
        location.x = floor(location.x);
        float sign = -(speed.x / fabsf(speed.x));
        while (stage->HitStage(this))location.x += sign;
    }
}

void Player::MoveY(Key* key, Stage* stage)//Ｙ座標の移動
{
    if ((speed.y += GRAVITY_POWER) > JUMP_SPEED)speed.y = JUMP_SPEED;//重力の大きさが一定に達すまでスピードに重力を足し続けて下に落とす。
    location.y += speed.y;//スピードをY座標に足す。

    if (stage->HitStage(this))//ステージにぶつかっていたら、
    {
        location.y = floor(location.y);
        float sign = -(speed.y / fabsf(speed.y));
        while (stage->HitStage(this))location.y += sign;

        speed.y = 0;

        if (sign == -1)//地面に触れているとき
        {
            if (key->KeyDown(A))speed.y = -JUMP_SPEED;
        }
    }
}

void Player::Draw(float camera_work) const
{
    DrawBox(location.x - radius.x + camera_work, location.y - radius.y, location.x + radius.x + camera_work, location.y + radius.y, 0xffffff, TRUE);
    
    if (can_use_item)
    {
        DrawRotaGraph(cursor_location.x + camera_work, cursor_location.y, 1, 0, cursor_image, TRUE);

        float gravity = 0;
        DATA throw_location = location;
        int count = 0;
        while (throw_location.y < SCREEN_HEIGHT)
        {
            throw_location.x -= throw_speed.x;
            throw_location.y -= (throw_speed.y - gravity);
            gravity += GRAVITY_POWER;
            if(!(++count % 3))DrawCircle(throw_location.x + camera_work, throw_location.y, 3, 0xffffff, FALSE);
        }
    }

    if (item_type == ITEM_TYPE::BLOCK)DrawString(0, 30, "ブロック", 0xffffff);
    else if(item_type == ITEM_TYPE::BOM)DrawString(0, 30, "爆弾", 0xffffff);
    else DrawString(0, 30, "つるはし", 0xffffff);
    //DrawFormatString(0, 30, 0xff0000, "左 %f", ((location.x - radius.x))/ STAGE_BLOCK_SIZE_X) - 1;
}