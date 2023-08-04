#pragma once
#include <vector>
#include"StageBlock.h"
#include"Treasure.h"
#include"BoxCollider.h"
#include"Effect.h"
#include"Bom.h"
#include"Pickaxe.h"
#include"define.h"

class Stage
{
private:

    int break_block_se;
    std::vector<StageBlock>stageblock;
    std::vector<class Treasure>treasure;
    std::vector<class Effect>effect;
    std::vector<class Bom>bom;
    class Pickaxe* pickaxe;
    int block_image[7];
    int treasure_image[4];
    int caveat_image;
    
    int effect_image[4][10];

public:

    Stage();
    ////�f�X�g���N�^
    ~Stage();
    //�`��ȊO�̍X�V����������
    void Update();
    //�`��Ɋւ��邱�Ƃ���������
    void Draw1(float camera_work) const;
    void Draw2(float camera_work) const;

    bool HitPickaxe(BoxCollider* bc);
    bool HitStage(BoxCollider* bc);
    TREASURE_TYPE HitTreasure(BoxCollider* bc, bool can_delete);
    bool PutItem(DATA location, ITEM_TYPE item_type);
    void ThrowItem(DATA location, DATA speed, ITEM_TYPE item_type);
};