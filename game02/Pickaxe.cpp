#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Pickaxe.h"

#define PICKAXE_SIZE_X 15
#define PICKAXE_SIZE_Y 15

Pickaxe::Pickaxe()
{
    radius = { PICKAXE_SIZE_X / 2, PICKAXE_SIZE_Y / 2};

    image = LoadGraph("images/Pickaxe/pickaxe.png");

    throw_pickaxe_se = LoadSoundMem("bgm/PickaxeThrow.mp3");
    hit_pickaxe_se = LoadSoundMem("bgm/hitpickaxe2.mp3");
    break_pickaxe_se = LoadSoundMem("bgm/breakpickaxe.mp3");

    can_throw_pickaxe_se = FALSE;
    can_throw = TRUE;
}

void Pickaxe::ThrowPickaxe(DATA location, DATA speed)
{
    if (can_throw)
    {
        this->location = location;
        old_location = location;
        this->speed = speed;

        angle = 0;
        angle_direction = 10;
        if (speed.x < 0)angle_direction = -10;

        PlaySoundMem(throw_pickaxe_se, DX_PLAYTYPE_LOOP, TRUE);
        can_throw_pickaxe_se = TRUE;
        can_throw = FALSE;
    }
}

void Pickaxe::Delete()
{
    DeleteSoundMem(throw_pickaxe_se);
    DeleteSoundMem(hit_pickaxe_se);
    DeleteSoundMem(break_pickaxe_se);

    DeleteGraph(image);
}

void Pickaxe::Update(Stage* stage)
{
    if (!can_throw)
    {
        old_location = location;

        speed.y += GRAVITY_POWER;
        location.y += speed.y;

        if (stage->HitPickaxe(this) && speed.y > 0)
        {
            can_throw = TRUE;
            StopSoundMem(throw_pickaxe_se);
            PlaySoundMem(break_pickaxe_se, DX_PLAYTYPE_BACK, TRUE);
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
                PlaySoundMem(hit_pickaxe_se, DX_PLAYTYPE_BACK, TRUE);
                StopSoundMem(throw_pickaxe_se);
                can_throw_pickaxe_se = FALSE;
            }
            angle += angle_direction;
            if (angle > 360)angle = 0;
            else if (angle < 0)angle = 360;
        }

        if (location.y > SCREEN_HEIGHT + 100)can_throw = TRUE, StopSoundMem(throw_pickaxe_se);
    }
}

void Pickaxe::Draw(float camera_work) const
{
    if (!can_throw)DrawRotaGraph(location.x + camera_work, location.y, 1, ((M_PI / 180) * angle), image, TRUE);
}

void Pickaxe::Pause(bool flg)
{
    if (flg)
    {
        StopSoundMem(throw_pickaxe_se);
    }
    else
    {
        if(can_throw_pickaxe_se) PlaySoundMem(throw_pickaxe_se, DX_PLAYTYPE_LOOP, TRUE);
    }
}