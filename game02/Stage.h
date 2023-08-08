#pragma once
#include <vector>
#include"StageBlock.h"
#include"Treasure.h"
#include"BoxCollider.h"
#include"Effect.h"
#include"Bom.h"
#include"Pickaxe.h"
#include"define.h"

#define BREAK_BLOCK_IMAGE_NUM 10
#define EXPLOSION_IMAGE_NUM 9

class Stage
{
private:

    std::vector<StageBlock>stageblock;
    std::vector<class Treasure>treasure;
    std::vector<class Effect>effect;
    std::vector<class Bom>bom;
    class Pickaxe* pickaxe;

    int effect_image[4][BREAK_BLOCK_IMAGE_NUM];
    int explosion_image[EXPLOSION_IMAGE_NUM];
    int pickaxe_image;
    int hit_pickaxe_se;
    int break_block_se;

public:

    Stage();
    ////デストラクタ
    ~Stage();
    //描画以外の更新を実装する
    void Update();
    //描画に関することを実装する
    void Draw1(float camera_work) const;
    void Draw2(float camera_work) const;

    bool HitPickaxe(BoxCollider* bc);
    bool HitStage(BoxCollider* bc);
    bool HitTreasure(BoxCollider* bc);
    bool HitBom(BoxCollider* bc);
    void HitBlastRange(int bom_num);
    TREASURE_TYPE GetTreasure(BoxCollider* bc);
    bool PutItem(DATA location, ITEM_TYPE item_type);
    void ThrowItem(DATA location, DATA speed, ITEM_TYPE item_type);
};