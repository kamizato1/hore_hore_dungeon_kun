#pragma once
#include <vector>
#include"BoxCollider.h"
#include"StageBlock.h"
#include"Treasure.h"
#include"Effect.h"
#include"Bom.h"
#include"Pickaxe.h"
#include"define.h"

#define BREAK_BLOCK_IMAGE_NUM 10
#define EXPLOSION_IMAGE_NUM 9

struct HIT_STAGE
{
    bool flg;
    int num;
    BLOCK_TYPE block_type;
};

struct HIT_TREASURE
{
    bool flg;
    int num;
    TREASURE_TYPE treasure_type;
};

struct HIT_BOM
{
    bool flg;
    int num;
};

class Stage
{
protected:

    std::vector<StageBlock>stageblock;
    std::vector<class Treasure>treasure;
    std::vector<class Effect>effect;
    std::vector<class Bom>bom;
    class Pickaxe* pickaxe;

    int effect_image[4][BREAK_BLOCK_IMAGE_NUM];
    int explosion_image[EXPLOSION_IMAGE_NUM];
    int smoke_image[EXPLOSION_IMAGE_NUM];
    int pickaxe_image;
    int hit_pickaxe_se;
    int break_block_se;

    void Init();

    


public:

    Stage();
    ////デストラクタ
    ~Stage();

    virtual void Update();

    virtual void Draw1(float camera_work) const;
    virtual void Draw2(float camera_work) const;

    bool HitPickaxe(BoxCollider* bc);

    HIT_STAGE HitStage(BoxCollider* bc);
    HIT_STAGE HitStage(DATA location, DATA radius);
    HIT_TREASURE HitTreasure(BoxCollider* bc);
    HIT_BOM HitBom(BoxCollider* bc);

    void DeleteTreasure(int num);
   // void DeleteBlock(int num) { stageblock.erase(stageblock.begin() + num); };

    void HitBlastRange(int bom_num);
    
    bool PutItem(DATA location, ITEM_TYPE item_type);
    void ThrowItem(DATA location, DATA speed, ITEM_TYPE item_type);
};