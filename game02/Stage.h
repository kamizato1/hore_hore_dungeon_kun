#pragma once
#include <vector>
#include"BoxCollider.h"
#include"Block.h"
#include"Treasure.h"
#include"Effect.h"
#include"Bom.h"
#include"Pickaxe.h"
#include"FallingBlock.h"
#include"define.h"

#define EFFECT_IMAGE_NUM 10
#define KIRA_KIRA_NUM 50

struct KIRA_KIRA
{
    DATA location;
    float size;
};

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

    std::vector<FallingBlock>fallingblock;
    std::vector<Block>block;
    std::vector<class Treasure>treasure;
    std::vector<class Effect>effect;
    std::vector<class Bom>bom;
    class Pickaxe* pickaxe;

    int back_ground_image[4];
    int falling_block_image;
    int break_block_image[8][EFFECT_IMAGE_NUM];
    int explosion_image[EFFECT_IMAGE_NUM];
    int smoke_image[EFFECT_IMAGE_NUM];
    int change_block_image[8][4];
    int pickaxe_image;
    int hit_pickaxe_se;
    int break_block_se;
    int image_change_time;
    int image_type;

    void Init();
    KIRA_KIRA kira_kira[KIRA_KIRA_NUM];
    int kira_kira_image[4];
   
public:

    Stage();
    ////デストラクタ
    ~Stage();

    virtual void Update();

    virtual void Draw1(float camera_work) const;
    virtual void Draw2(float camera_work) const;

    bool HitPickaxe(BoxCollider* bc);

    HIT_STAGE HitStage(BoxCollider* bc);
    HIT_TREASURE HitTreasure(BoxCollider* bc);
    HIT_BOM HitBom(BoxCollider* bc);

    void DeleteTreasure(int num);

    void HitBlastRange(int bom_num);
    
    bool PutItem(BoxCollider* bc, ITEM_TYPE item_type, int item_num);
    bool ThrowItem(DATA location, DATA speed, ITEM_TYPE item_type, int item_num);
    void Sway();
    bool GetPickaxeFlg();
};