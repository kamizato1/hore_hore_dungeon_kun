#include"DxLib.h"
#include"Block.h"

Block::Block(DATA location, int type)
{
    radius = { BLOCK_SIZE_X / 2 ,BLOCK_SIZE_Y / 2};
    this->location = location;
    SetBlockType(type);
    hit_explosion = FALSE;
}

void Block::SetBlockType(int type)
{ 
    this->type = static_cast<BLOCK_TYPE>(type);
}