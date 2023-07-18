#pragma once

//#include <vector>
#include"StageBlock.h"
#include"Item.h"
#include"BoxCollider.h"
#include"define.h"

class Stage
{
private:

    int break_block_se;
    StageBlock* stageblock[STAGE_BLOCK_NUM_Y][STAGE_BLOCK_NUM_X];
    class Item* item[15];
    int block_image[7];

public:

    Stage();
    ////デストラクタ
    ~Stage();
    //描画以外の更新を実装する
    void Update();
    //描画に関することを実装する
    void Draw(float camera_work) const;

    bool HitPickaxe(BoxCollider* bc);
    bool HitStage(BoxCollider* bc);

    void UseItem(int x, int y, ITEM_TYPE item_type);
};