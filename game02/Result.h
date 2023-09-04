#pragma once
#include "AbstractScene.h"

#define TREASURE_NUM 3

class Result : public AbstractScene
{
private:

    int score;
    int map_image;
    int score_image;
    int back_ground_image[3];
    int number_image[10];

    float score_image_size;
    float score_image_angle;
    float move_back_ground_image[3];

    int treasure_num[TREASURE_NUM];

    bool end_move_score;

    //�J�ڂ���̂�
    bool transition;

public:

    Result(int block_break,int time ,int item_block);//�󂵂��u���b�N�̐��A���ԁA�����Ă���u���b�N�̐�,��̎�ނƎ��    
    ~Result(); //�f�X�g���N�^

    void Update(Key* key) override;//�`��ȊO�̍X�V����������
    void Draw() const override;//�`��Ɋւ��邱�Ƃ���������
    AbstractScene* ChangeScene() override;//�V�[���؂�ւ�

    void MoveScore();
};

