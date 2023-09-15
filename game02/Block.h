#pragma once

#include"BoxCollider.h"
#include"define.h"

struct GET_DRAW_BLOCK
{
    DATA location;
    bool hit_explosion;
    int block_type;
};

class Block : public BoxCollider
{
private:

    BLOCK_TYPE type;
    bool hit_explosion;

public:

    Block(DATA location, int type);
    BLOCK_TYPE GetBlockType() const{ return type; }
    void SetBlockType(int type);
    void SetHitEcplosion(bool flg) { hit_explosion = flg; }
    GET_DRAW_BLOCK GetDrawBlock() const;
};