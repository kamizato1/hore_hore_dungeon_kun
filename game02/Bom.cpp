#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Bom.h"

#define BOM_COUNT 6
#define EXPLOSION_SIZE BLOCK_SIZE_X * 7
#define BOM_SIZE_CHANGE_TIME 6

Bom::Bom(DATA location, DATA speed)
{
    this->location = location;
    this->speed = speed;
    throw_flg = TRUE;
    if ((speed.x == 0) && (speed.y == 0))throw_flg = FALSE;
    radius = { BLOCK_SIZE_X / 2, BLOCK_SIZE_Y / 2 };
    image = LoadGraph("images/angrybom.png");
    blast_range_image = LoadGraph("images/wakuwaku.png");
    LoadDivGraph("images/bomnumber.png", 6, 6, 1, 14, 23, number_image);
    can_delete = FALSE;
    angle = 0;
    angle_direction = 3;
    if (speed.x > 0)angle_direction = -3;
    count = FPS * BOM_COUNT;
    bom_size = 1;
    bom_size_add = 0.1;
    bom_size_change_time = BOM_SIZE_CHANGE_TIME * 2;
    old_hit = FALSE;
}

void Bom::Update(StageBase* stagebase)
{
    if (--bom_size_change_time == 0)
    {
        bom_size_change_time = BOM_SIZE_CHANGE_TIME;
        bom_size += bom_size_add;
        if (bom_size >= 1.3)bom_size_add = -0.1;
        else if (bom_size <= 1.0)
        {
            bom_size_add = 0.1;
            bom_size_change_time = BOM_SIZE_CHANGE_TIME * 2;
        }
    }

    if (throw_flg)
    {
        speed.y += GRAVITY_POWER;
        location.y += speed.y;

        location.x += speed.x;
        
        angle += angle_direction;

        if (stagebase->HitStage(this).flg)can_delete = TRUE;
    }
    else
    {
        if (!stagebase->HitStage(this).flg)location.y += 1;
        if(stagebase->HitStage(this).flg)
        {
            int y = location.y / BLOCK_SIZE_Y;
            location.y = (y * BLOCK_SIZE_Y) + (radius.y);
        }

        if (--count <= 0)can_delete = TRUE;
    }
}

bool Bom::HitExplosion(BoxCollider* bc)const
{
    bool flg = FALSE;
    DATA radius = { EXPLOSION_SIZE / 2, EXPLOSION_SIZE / 2};
    if (HitBox(bc, location, radius))flg = TRUE;
    return flg;
}

void Bom::Draw(float camera_work) const
{
    int count = this->count / FPS;
    DrawRotaGraph(location.x + camera_work, location.y, bom_size, ((M_PI / 180) * angle), image, TRUE);
    if(!throw_flg)DrawRotaGraph((location.x - 2) + camera_work, location.y + 1, bom_size, 0, number_image[count], TRUE);
    DrawRotaGraph(location.x + camera_work, location.y, 1, 0, blast_range_image, TRUE);
}