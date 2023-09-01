#include"DxLib.h"
#include <math.h>
#include"Cursor.h"

Cursor::Cursor(DATA location)
{
    radius = { BLOCK_SIZE_X / 2 ,BLOCK_SIZE_Y / 2 };
    this->location = location;
    image = LoadGraph("images/cursor.png");
    cursor_sign_x = 1;
    cursor_sign_y = 0;
    hit_player = FALSE;
}

void Cursor::Update(BoxCollider* bc, DATA r_stick_angle)
{
    if ((r_stick_angle.x != 0) || (r_stick_angle.y != 0))
    {
        if (r_stick_angle.x == 0)cursor_sign_x = 0;
        else if (r_stick_angle.x < 0)cursor_sign_x = -1;
        else cursor_sign_x = 1;
        if (r_stick_angle.y == 0)cursor_sign_y = 0;
        else if (r_stick_angle.y < 0)cursor_sign_y = -1;
        else cursor_sign_y = 1;
    }

    location = bc->GetLocation();
    int x = location.x / BLOCK_SIZE_X;
    int y = location.y / BLOCK_SIZE_Y;
    location.x = (x * BLOCK_SIZE_X) + radius.x;
    location.y = (y * BLOCK_SIZE_Y) + radius.y;

    if (cursor_sign_y == 0)while (HitBox(bc))location.x += (BLOCK_SIZE_X * cursor_sign_x);
    else
    {
        while (HitBox(bc))location.y += (BLOCK_SIZE_Y * cursor_sign_y);
        location.x += (BLOCK_SIZE_X * cursor_sign_x);  
    }

    if (HitBox(bc))hit_player = TRUE;
}

void Cursor::Draw(float camera_work) const
{
    DrawRotaGraphF(location.x + camera_work, location.y, 1, 0, image, TRUE);
    DrawFormatString(0, 130, 0xffffff, "%d = hit_player (これが'1'なら（Cursor）エラーです。)", hit_player);
}