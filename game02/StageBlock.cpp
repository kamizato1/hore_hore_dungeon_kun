#include"DxLib.h"
#include"StageBlock.h"

StageBlock::StageBlock(int x, int y, int type, int image)
{
    radius = { STAGE_BLOCK_SIZE_X / 2 ,STAGE_BLOCK_SIZE_Y / 2};
    location.x = (x * STAGE_BLOCK_SIZE_X) + radius.x;
    location.y = (y * STAGE_BLOCK_SIZE_Y) + radius.y;
    this->type = static_cast<BLOCK_TYPE>(type);
    this->image = image;
}

void StageBlock::Update()
{

}

void StageBlock::Draw(float camera_work) const
{
    DrawRotaGraph(location.x + camera_work, location.y, 1, 0, image, TRUE, TRUE);
}

void StageBlock::SetBlockType(BLOCK_TYPE type, int image)
{ 
    this->type = type;
    this->image = image;
}