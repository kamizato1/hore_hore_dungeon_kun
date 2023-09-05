#pragma once
#include "AbstractScene.h"

#define TREASURE_NUM 4

class Result : public AbstractScene
{
private:

    int score;
    int treasure_num[TREASURE_NUM];
    int treasure_score[TREASURE_NUM];
    int treasure_price[TREASURE_NUM];

    int stamp_image;
    int sign_image[3];
    int treasure_image[TREASURE_NUM];
    int map_image;
    int score_image;
    int back_ground_image[3];
    int number_image[10];

    int wait_time;

    float score_image_size;
    float score_image_angle;

    float back_ground_image_x[3];

    float stamp_image_size;
    
    bool end_add_score;
    bool end_move_score;
    bool end_move_stamp;
    bool stamp_flg;
    bool skip;
    bool new_record;

    //�J�ڂ���̂�
    bool transition;

public:

    Result(int stage_num, int* treasure_num);//�󂵂��u���b�N�̐��A���ԁA�����Ă���u���b�N�̐�,��̎�ނƎ��    
    ~Result(); //�f�X�g���N�^

    void Update(Key* key) override;//�`��ȊO�̍X�V����������
    void Draw() const override;//�`��Ɋւ��邱�Ƃ���������
    AbstractScene* ChangeScene() override;//�V�[���؂�ւ�

    void MoveScore();
    void AddScore();
    void MoveStamp();
};

