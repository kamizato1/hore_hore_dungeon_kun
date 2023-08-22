#include"DxLib.h"
#include"Block.h"

Block::Block(DATA location, int type)
{
    radius = { BLOCK_SIZE_X / 2 ,BLOCK_SIZE_Y / 2};
    this->location = location;
    this->type = static_cast<BLOCK_TYPE>(type);
    int image[7];
    LoadDivGraph("images/block01.png", 7, 7, 1, BLOCK_SIZE_X, BLOCK_SIZE_Y, image);
    this->image = image[type];
    caveat_image = LoadGraph("images/warning.png");
    hit_explosion = FALSE;
}

void Block::Update()
{

}

void Block::Draw(float camera_work) const
{
    DrawRotaGraphF(location.x + camera_work, location.y, 1, 0, image, TRUE);
    if(hit_explosion)DrawRotaGraphF(location.x + camera_work, location.y, 1, 0, caveat_image, TRUE);
}

void Block::SetBlockType(int type)
{ 
    this->type = static_cast<BLOCK_TYPE>(type);
    int image[7];
    LoadDivGraph("images/block01.png", 7, 7, 1, BLOCK_SIZE_X, BLOCK_SIZE_Y, image);
    this->image = image[type];
}