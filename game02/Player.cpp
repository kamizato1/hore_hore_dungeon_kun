#include"DxLib.h"
#include <math.h>

#include"Player.h"

#define PLAYER_SIZE_X 25
#define PLAYER_SIZE_Y 25

#define JUMP_SPEED 10


Player::Player()
{
    pickaxe = nullptr;
    location = { 10, 300 };
    cursor_location = location;
    radius = { PLAYER_SIZE_X / 2, PLAYER_SIZE_Y / 2 };
    speed = { 0,0 };
    pickaxe_speed = { 0,0 };
   
    for (int i = 0; i < R_STICK_ANGLE_RECORD_NUM; i++)r_stick_angle_record[i] = { 0,0 };
    for (int i = 0; i < SPEED_X_RECORD_NUM; i++)speed_x_record[i] = 0;

    cursor_image = LoadGraph("images/cursor.png");
    item_type = ITEM_TYPE::PICKAXE;
    can_use_item = FALSE;
}

void Player::Update(Key* key, Stage* stage)
{
    //ここから下↓プレイヤーの移動処理

    //ここから下↓x座標の移動
    float all_speed_x_record_calculation = 0;
    float now_speed_x, old_speed_x;
   
    now_speed_x = 0;
    if (key->KeyPressed(RIGHT))now_speed_x = 2;
    else if (key->KeyPressed(LEFT))now_speed_x = -2;

    for (int i = 0; i < SPEED_X_RECORD_NUM; i++)
    {
        old_speed_x = speed_x_record[i];
        speed_x_record[i] = now_speed_x;
        now_speed_x = old_speed_x;
        all_speed_x_record_calculation += speed_x_record[i];
    }

    speed.x = (all_speed_x_record_calculation / SPEED_X_RECORD_NUM);
    location.x += speed.x;

    if (stage->HitStage(this))
    {
        location.x = floor(location.x);
        float sign = -(speed.x / fabsf(speed.x));
        while (stage->HitStage(this))location.x += sign;
    }

    //ここから下↓y座標の移動

    if ((speed.y += GRAVITY_POWER) > JUMP_SPEED)speed.y = JUMP_SPEED;
    location.y += speed.y;

    if (stage->HitStage(this))
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

    //ここから下↓つるはしを投げるときの処理

    DATA all_r_stick_angle_record_calculation = { 0,0 };
    DATA now_r_stick_angle, old_r_stick_angle;

    now_r_stick_angle.x = -(key->GetStickAngle(R).x / 60);
    now_r_stick_angle.y = -(key->GetStickAngle(R).y / 60);
    
    for (int i = 0; i < R_STICK_ANGLE_RECORD_NUM; i++)
    {
        old_r_stick_angle = r_stick_angle_record[i];
        r_stick_angle_record[i] = now_r_stick_angle;
        now_r_stick_angle = old_r_stick_angle;
        all_r_stick_angle_record_calculation.x += r_stick_angle_record[i].x;
        all_r_stick_angle_record_calculation.y += r_stick_angle_record[i].y;
    }

    pickaxe_speed.x = (all_r_stick_angle_record_calculation.x / R_STICK_ANGLE_RECORD_NUM);
    pickaxe_speed.y = (all_r_stick_angle_record_calculation.y / R_STICK_ANGLE_RECORD_NUM);

    if ((pickaxe_speed.x == 0) && (pickaxe_speed.y == 0))can_use_item = FALSE;
    else can_use_item = TRUE;

    int cursor_sign_x = 0;
    if (pickaxe_speed.x != 0)cursor_sign_x = -(pickaxe_speed.x / fabsf(pickaxe_speed.x));
    int cursor_sign_y = 0;
    if (pickaxe_speed.y != 0)cursor_sign_y = -(pickaxe_speed.y / fabsf(pickaxe_speed.y));

    int cursor_x_num = (location.x / STAGE_BLOCK_SIZE_X) + cursor_sign_x;
    if (cursor_sign_y == 0)cursor_x_num = (location.x + (radius.x * cursor_sign_x)) / STAGE_BLOCK_SIZE_X + cursor_sign_x;
    int cursor_y_num = (location.y + (radius.y * cursor_sign_y)) / STAGE_BLOCK_SIZE_Y + cursor_sign_y;

    cursor_location.x = (cursor_x_num * STAGE_BLOCK_SIZE_X) + (STAGE_BLOCK_SIZE_X / 2);
    cursor_location.y = (cursor_y_num * STAGE_BLOCK_SIZE_Y) + (STAGE_BLOCK_SIZE_Y / 2);

    if(pickaxe != nullptr)
    {
        if (pickaxe->CanDelete())pickaxe = nullptr;
        else pickaxe->Update(stage);
    }

    if (can_use_item)
    {
        if (pickaxe == nullptr)
        {
            if (key->KeyDown(L))pickaxe = new Pickaxe(location, pickaxe_speed);
        }
        if (key->KeyDown(R))stage->UseItem(cursor_x_num, cursor_y_num, ITEM_TYPE::BLOCK);
    }
}

void Player::Draw(float camera_work) const
{
    DrawBox(location.x - radius.x + camera_work, location.y - radius.y, location.x + radius.x + camera_work, location.y + radius.y, 0xffffff, TRUE);
    
    if (can_use_item)
    {
        DrawRotaGraph(cursor_location.x + camera_work, cursor_location.y, 1, 0, cursor_image, TRUE);

        float gravity = 0;
        DATA draw_pickaxe = location;
        while (draw_pickaxe.y < SCREEN_HEIGHT)
        {
            draw_pickaxe.x -= pickaxe_speed.x;
            draw_pickaxe.y -= (pickaxe_speed.y - gravity);
            gravity += GRAVITY_POWER;
            DrawCircle(draw_pickaxe.x + camera_work, draw_pickaxe.y, 3, 0xffffff, FALSE);
        }
    }

    if (pickaxe != nullptr)pickaxe->Draw(camera_work);
}