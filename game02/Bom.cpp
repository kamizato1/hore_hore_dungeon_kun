#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Bom.h"

#define BOM_COUNT 5
#define EXPLOSION_SIZE BLOCK_SIZE_X * 7

Bom::Bom(DATA location, DATA speed)
{
    this->location = location;
    this->speed = speed;
    throw_flg = TRUE;
    if ((speed.x == 0) && (speed.y == 0))throw_flg = FALSE;
    radius = { BLOCK_SIZE_X / 2, BLOCK_SIZE_Y / 2 };
    image = LoadGraph("images/angrybom.png");
    blast_range_image = LoadGraph("images/wakusen.png");
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
        if(stage->HitStage(this))
        {
            int y = location.y / BLOCK_SIZE_Y;
            location.y = (y * BLOCK_SIZE_Y) + (radius.y);
        }

        if (--count <= 0)can_delete = TRUE;
    }

    if (location.y > SCREEN_HEIGHT)can_delete = TRUE;
}

bool Bom::HitExplosion(BoxCollider* bc)const
{
    bool flg = FALSE;
    DATA radius = { EXPLOSION_SIZE / 2, EXPLOSION_SIZE / 2};
    if (AllHitBox(bc, location, radius))flg = TRUE;
    return flg;
}

void Bom::Draw(float camera_work) const
{
    DrawRotaGraph(location.x + camera_work, location.y, 1, ((M_PI / 180) * angle), image, TRUE);
    if (!throw_flg)DrawFormatString(location.x + camera_work, location.y - 30, 0xffffff, "%d", count / FPS);
    //DrawBox(location.x - (EXPLOSION_SIZE / 2) + camera_work, location.y - (EXPLOSION_SIZE / 2), location.x + (EXPLOSION_SIZE / 2) + camera_work, location.y + (EXPLOSION_SIZE / 2), 0xffffff, FALSE);
    DrawRotaGraph(location.x + camera_work, location.y, 1, 0, blast_range_image, TRUE);
}