#pragma once
#include <vector>
#include"BoxCollider.h"
#include"Block.h"
#include"Treasure.h"
#include"Flag.h"
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
    bool can_put;
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
    Flag *flag;

    //ブロック
    int set_block_image[32];
    int block_image[BLOCK_TYPE_NUM][4];
    int block_warning_image;

    //爆弾
    int bom_image;
    int bom_frame_image;
    int bom_number_image[6];

    //宝
    int treasure_image[TREASURE_TYPE_NUM];

    //旗
    int flag_image[4];

    //壊れるエフェクト
    int set_break_block_image[80];
    int set_break_treasure_image[50];
    int break_block_image[BLOCK_TYPE_NUM][EFFECT_IMAGE_NUM];
    int break_treasure_image[TREASURE_TYPE_NUM][EFFECT_IMAGE_NUM];
    //爆発エフェクト
    int explosion_image[EFFECT_IMAGE_NUM];
    int smoke_image[EFFECT_IMAGE_NUM];

    //地震ブロック
    int falling_block_image;

    int back_ground_image[4];
    int kira_kira_image[4];
    
    int hit_hard_block_se;
    int break_block_se;
    int explosion_se;
    int break_treasure_se;
    int put_item_se;

    int image_change_time;
    int image_type;
    int break_block_num;
    DATA flag_location;
    KIRA_KIRA kira_kira[KIRA_KIRA_NUM];
   
public:

    Stage(int stage_num, int stage_width);
    void Delete();

    void LoadImages();

    void Update();
    void Draw1(float camera_work) const;
    void Draw2(float camera_work) const;

    bool HitPickaxe(BoxCollider* bc);

    HIT_STAGE HitBlock(BoxCollider* bc);
    HIT_TREASURE HitTreasure(BoxCollider* bc, bool is_it_treasure);
    HIT_BOM HitBom(BoxCollider* bc, bool is_it_bom);
    bool HitFlag(BoxCollider* bc);

    void DeleteTreasure(int num);
    void HitBlastRange(int bom_num);
    bool PutItem(BoxCollider* bc, ITEM_TYPE item_type);
    void ThrowItem(DATA location, DATA speed, ITEM_TYPE item_type);
    void Sway();
    bool GetPickaxeFlg();
    int GetBreakBlockNum() { return break_block_num; }
    void DeleteFlag();
    void Init();
    void Pause(bool flg);

    
};