#pragma once

#include"BoxCollider.h"
#include"define.h"



class Block : public BoxCollider
{
private:

    BLOCK_TYPE type;
    int image;
    int caveat_image;
    bool hit_explosion;

public:

    Block(DATA location, int type, int image);
    void Delete();

    //•`‰æ‚ÉŠÖ‚·‚é‚±‚Æ‚ðŽÀ‘•‚·‚é
    void Draw(float camera_work) const;

    BLOCK_TYPE GetBlockType() { return type; }
    void SetBlockType(int type, int image);
    void SetHitEcplosion(bool flg) { hit_explosion = flg; }
    void SetBlockImage(int image);
};