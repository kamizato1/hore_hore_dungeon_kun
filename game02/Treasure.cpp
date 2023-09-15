#include"DxLib.h"
#include"Treasure.h"

Treasure::Treasure(DATA location, int type)
{
    radius = { BLOCK_SIZE_X / 2 ,BLOCK_SIZE_Y / 2 };
    this->location = location;
    this->type = static_cast<TREASURE_TYPE>(type);
    old_hit = FALSE;
    can_delete = FALSE;
}


void Treasure::Update(Stage* stage)
{
    if ((!stage->HitBlock(this).flg) && (!stage->HitBom(this, FALSE).flg) && (!stage->HitTreasure(this, TRUE).flg))location.y += 1;
    if ((stage->HitBlock(this).flg) || (stage->HitBom(this, FALSE).flg) || (stage->HitTreasure(this, TRUE).flg))
    {
        int y = location.y / BLOCK_SIZE_Y;
        location.y = (y * BLOCK_SIZE_Y) + (radius.y);
    }
    if (location.y > SCREEN_HEIGHT)can_delete = TRUE;
}

bool Treasure::GetOldHit(Stage* stage)
{
    if (stage->HitBlock(this).flg)
    {
        old_hit = TRUE;
        return TRUE;
    }
    else if (old_hit)return TRUE;

    return FALSE;
}