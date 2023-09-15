#pragma once

#include"BoxCollider.h"
#include"define.h"



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
};