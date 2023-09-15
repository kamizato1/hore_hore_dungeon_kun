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

GET_DRAW_BLOCK Block::GetDrawBlock()const
{
    GET_DRAW_BLOCK get_draw_block;
    get_draw_block.location = location;
    get_draw_block.hit_explosion = hit_explosion;
    get_draw_block.block_type = static_cast<int>(type);

    return get_draw_block;
}