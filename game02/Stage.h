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
    ////�f�X�g���N�^
    ~Stage();
    //�`��ȊO�̍X�V����������
    void Update();
    //�`��Ɋւ��邱�Ƃ���������
    void Draw(float camera_work) const;

    bool HitPickaxe(BoxCollider* bc);
    bool HitStage(BoxCollider* bc);

    bool UseItem(DATA location, ITEM_TYPE item_type);
};