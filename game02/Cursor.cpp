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
}

void Cursor::Update(BoxCollider* bc, DATA r_stick_angle)
{
    if ((r_stick_angle.x != 0) || (r_stick_angle.y != 0))
    {
        if (r_stick_angle.x == 0)cursor_sign_x = 0;
        else cursor_sign_x = r_stick_angle.x / fabsf(r_stick_angle.x);
        if (r_stick_angle.y == 0)cursor_sign_y = 0;
        else cursor_sign_y = r_stick_angle.y / fabsf(r_stick_angle.y);
    }

    int x = bc->GetLocation().x / BLOCK_SIZE_X;
    int y = bc->GetLocation().y / BLOCK_SIZE_Y;

    location.x = (x * BLOCK_SIZE_X) + radius.x;
    location.y = (y * BLOCK_SIZE_Y) + radius.y;

    while (HitBox(bc))
    {
        location.x += (BLOCK_SIZE_X * cursor_sign_x);
        location.y += (BLOCK_SIZE_Y * cursor_sign_y);
    }
}

void Cursor::Draw(float camera_work) const
{
    DrawRotaGraphF(location.x + camera_work, location.y, 1, 0, image, TRUE);
    DrawFormatString(0, 200, 0xffffff, "%d", cursor_sign_x);
    DrawFormatString(0, 225, 0xffffff, "%d", cursor_sign_y);
}