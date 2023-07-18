#include"DxLib.h"
#include"Item.h"

Item::Item(int x, int y, int type, int image)
{
    radius = { 25 / 2 ,25 / 2 };
    location.x = (x * STAGE_BLOCK_SIZE_X) + radius.x;
    location.y = (y * STAGE_BLOCK_SIZE_Y) + radius.y;
    this->treasure_type = static_cast<TREASURE_TYPE>(type);
    this->image = image;
}

void Item::Update(Stage* stage)
{
    if (stage->HitStage(this))location.y += 1;
}

void Item::Draw(float camera_work) const
{
    DrawRotaGraph(location.x + camera_work, location.y, 1, 0, image, TRUE, TRUE);
}