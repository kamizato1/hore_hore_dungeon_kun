#include"DxLib.h"
#include"Treasure.h"

Treasure::Treasure(int x, int y, TREASURE_TYPE type, int image)
{
    radius = { BLOCK_SIZE_X / 2 ,BLOCK_SIZE_Y / 2 };
    location.x = (x * BLOCK_SIZE_X) + (BLOCK_SIZE_X / 2);
    location.y = (y * BLOCK_SIZE_Y) + (BLOCK_SIZE_Y / 2);
    this->type = type;
    this->image = image;
    old_hit = FALSE;
    can_delete = FALSE;
}

void Treasure::Update(Stage* stage)
{
    if (!stage->HitStage(this))location.y += 1;
    if (stage->HitStage(this))
    {
        int y = location.y / BLOCK_SIZE_Y;
        location.y = (y * BLOCK_SIZE_Y) + (radius.y);
    }
    if (location.y > SCREEN_HEIGHT)can_delete = TRUE;
}

void Treasure::Draw(float camera_work) const
{
    DrawRotaGraph(location.x + camera_work, location.y, 1, 0, image, TRUE);
}

bool Treasure::HitDamage(bool hit_type, Stage* stage)
{
    if (hit_type)
    {
        if ((!stage->HitStage(this)) && (!old_hit))return TRUE;
        old_hit = TRUE;
    }
    else
    {
        if (!stage->HitStage(this))return TRUE;
    }
    return FALSE;
}