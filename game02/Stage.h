#pragma once
#include <vector>
#include"StageBlock.h"
#include"Treasure.h"
#include"BoxCollider.h"
#include"BreakBlock.h"
#include"define.h"

class Stage
{
private:

    int break_block_se;
    std::vector<StageBlock>stageblock;
    std::vector<class Treasure>treasure;
    std::vector<class BreakBlock>breakblock;
    int block_image[7];
    int treasure_image[4];

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

    bool UseItem(DATA location, ITEM_TYPE item_type);
};