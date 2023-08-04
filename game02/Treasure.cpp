#include"DxLib.h"
#include"Treasure.h"

Treasure::Treasure(int x, int y, int type, int image)
{
    radius = { BLOCK_SIZE_X / 2 ,BLOCK_SIZE_Y / 2 };
    location.x = (x * BLOCK_SIZE_X) + (BLOCK_SIZE_X / 2);
    location.y = (y * BLOCK_SIZE_Y) + (BLOCK_SIZE_Y / 2);
    treasure_type = static_cast<TREASURE_TYPE>(type);
    this->image = image;
}

void Treasure::Update(Stage* stage)
{
    if (!stage->HitStage(this))location.y += 1;
}

void Treasure::Draw(float camera_work) const
{
    DrawRotaGraph(location.x + camera_work, location.y, 1, 0, image, TRUE, TRUE);
}