#pragma once

#include"BoxCollider.h"
#include"define.h"



class StageBlock : public BoxCollider
{
private:

    BLOCK_TYPE type;
    int image;
    int caveat_image;
    bool hit_explosion;

public:

    StageBlock(DATA location, int type);

    //描画以外の更新を実装する
    void Update();
    //描画に関することを実装する
    void Draw(float camera_work) const;

    BLOCK_TYPE GetBlockType() { return type; }
    void SetBlockType(int type);
    void SetHitEcplosion(bool flg) { hit_explosion = flg; }
};