#include"DxLib.h"
#include"Block.h"

Block::Block(DATA location, int type, int image)
{
    radius = { BLOCK_SIZE_X / 2 ,BLOCK_SIZE_Y / 2};
    this->location = location;
    SetBlockType(type, image);
    caveat_image = LoadGraph("images/warning.png");
    hit_explosion = FALSE;
}

void Block::Delete()
{
    DeleteGraph(image);
    DeleteGraph(caveat_image);
}

void Block::Draw(float camera_work) const
{
    DrawRotaGraphF(location.x + camera_work, location.y, 1, 0, image, TRUE);
    if(hit_explosion)DrawRotaGraphF(location.x + camera_work, location.y, 1, 0, caveat_image, TRUE);
}

void Block::SetBlockType(int type, int image)
{ 
    SetBlockImage(image);
    this->type = static_cast<BLOCK_TYPE>(type);
}

void Block::SetBlockImage(int image)
{
    this->image = image;
}