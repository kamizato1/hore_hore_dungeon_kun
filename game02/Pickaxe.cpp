#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Pickaxe.h"

#define PICKAXE_SIZE_X 15
#define PICKAXE_SIZE_Y 15

Pickaxe::Pickaxe(DATA location, DATA speed, int image, int se)
{
    this->location = location;
    old_location = location;
    this->speed = speed;
    radius = { PICKAXE_SIZE_X / 2, PICKAXE_SIZE_Y / 2};
    this->image = image;
    this->se = se;
    can_delete = FALSE;
    angle = 0;
    angle_direction = 10;
    if (speed.x < 0)angle_direction = -10;
    
}

void Pickaxe::Update(Stage* stage)
{
    old_location = location;

    speed.y += GRAVITY_POWER;
    location.y += speed.y;

    if (stage->HitPickaxe(this) && speed.y > 0)
    {
        can_delete = TRUE;
        PlaySoundMem(se, DX_PLAYTYPE_BACK, TRUE);
    }
    else
    {
        location.x += speed.x;
        if (stage->HitPickaxe(this))
        {
            location = old_location;
            speed.x = 0;
            speed.y = 0;
            angle_direction = -(angle_direction / 2);
            PlaySoundMem(se, DX_PLAYTYPE_BACK, TRUE);
        }
        angle += angle_direction;
        if (angle > 360)angle = 0;
        else if (angle < 0)angle = 360;
    }

    if (location.y > SCREEN_HEIGHT)can_delete = TRUE;
}

void Pickaxe::Draw(float camera_work) const
{
    DrawRotaGraph(location.x + camera_work, location.y, 1, ((M_PI / 180) * angle), image, TRUE);
}