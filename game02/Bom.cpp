#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Bom.h"

#define BOM_RADIUS ITEM_SIZE_X / 2
#define BOM_COUNT 5
#define EXPLOSION_RADIUS STAGE_BLOCK_SIZE_X * 7

Bom::Bom(DATA location, DATA speed)
{
    this->location = location;
    this->speed = speed;
    throw_flg = TRUE;
    if ((speed.x == 0) && (speed.y == 0))throw_flg = FALSE;
    radius = { BOM_RADIUS, BOM_RADIUS };
    image = LoadGraph("images/angrybom.png");
    can_delete = FALSE;
    angle = 0;
    angle_direction = 3;
    if (speed.x > 0)angle_direction = -3;
    count = FPS * BOM_COUNT;
}

void Bom::Update(Stage* stage)
{
    if (throw_flg)
    {
        location.y -= speed.y;
        location.x -= speed.x;
        speed.y -= GRAVITY_POWER;
        angle += angle_direction;

        if (stage->HitStage(this))can_delete = TRUE;
    }
    else
    {
        if (!stage->HitStage(this))location.y += 1;
        if (--count <= 0)can_delete = TRUE;
    }

    if (location.y > SCREEN_HEIGHT)can_delete = TRUE;
}

bool Bom::HitExplosion(BoxCollider* bc)const
{
    bool flg = FALSE;
    DATA radius = { EXPLOSION_RADIUS / 2, EXPLOSION_RADIUS / 2 };
    if (HitBox(bc, location, radius))flg = TRUE;
    return flg;
}

void Bom::Draw(float camera_work) const
{
    DrawRotaGraph(location.x + camera_work, location.y, 1, ((M_PI / 180) * angle), image, TRUE);
    if (!throw_flg)DrawFormatString(location.x + camera_work, location.y - 30, 0xffffff, "%d", count / FPS);
}