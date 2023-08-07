#pragma once

#include"BoxCollider.h"
#include"define.h"

enum class BLOCK_TYPE
{
    NONE,//ブロックが置けない
    BROKEN_BLOCK,//壊れそうなブロック
    WOUNDED_BLOCK,//傷ついているブロック
    NORMAL_BLOCK,//ブロック
    GROUND_BLOCK,//地面のブロック
    HARD_BLOCK,//かたいブロック
    VERY_HARD_BLOCK//とても固いブロック
};

class StageBlock : public BoxCollider
{
private:

    BLOCK_TYPE type;
    int image;
    int caveat_image;
    bool hit_explosion;

public:

    StageBlock(int x, int y, BLOCK_TYPE type, int image, int caveat_image);

    //描画以外の更新を実装する
    void Update();
    //描画に関することを実装する
    void Draw(float camera_work) const;

    BLOCK_TYPE GetBlockType() { return type; }
    void SetBlockType(BLOCK_TYPE type, int image);
    void SetHitEcplosion(bool flg) { hit_explosion = flg; }
};