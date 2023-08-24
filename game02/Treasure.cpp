#include"DxLib.h"
#include"Treasure.h"

Treasure::Treasure(DATA location, int type)
{
    radius = { BLOCK_SIZE_X / 2 ,BLOCK_SIZE_Y / 2 };
    this->location = location;
    this->type = static_cast<TREASURE_TYPE>(type);
    int image[3];
    LoadDivGraph("images/treasure1.png", 3, 3, 1, BLOCK_SIZE_X, BLOCK_SIZE_Y, image);
    this->image = image[type];
    old_hit = FALSE;
    can_delete = FALSE;
}

void Treasure::Update(Stage* stage)
{
    if (!stage->HitStage(this).flg)location.y += 1;
    if (stage->HitStage(this).flg)
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

bool Treasure::GetOldHit(Stage* stage, bool hit_type)
{
    bool flg = FALSE;

    if (hit_type)//”š’e‚Ìê‡
    {
        if (stage->HitStage(this).flg)flg = TRUE;
    }
    else//ƒsƒbƒPƒ‹‚Ìê‡
    {
        if (stage->HitStage(this).flg)old_hit = TRUE, flg = TRUE;
        else if (old_hit)flg = TRUE;
    }
    return flg;
}