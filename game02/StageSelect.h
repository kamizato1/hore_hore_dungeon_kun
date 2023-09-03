#pragma once
#include "AbstractScene.h"

#define STAGE_NUM 3

//�X�e�[�W�Z���N�g��ʂɂ��āi�R�X�e�[�W�j
//New �X�[�p�[�}���I�u���U�[�Y�̃X�e�[�W�I����ʂ��Q�l�ɂ���B

class StageSelect : public AbstractScene
{
private:

    int stage_number;//���ݑI�𒆂̃X�e�[�W�ԍ�
    int stage_score[STAGE_NUM];
    int stage_width[STAGE_NUM];
    int number_image[10];

    int operating_time;//�����t

    int back_ground_image;//�w�i�摜
    int player_image;

    //�J�[�\���̍��W
    float cursor_x;
    float cursor_y;

    

    //���̉�ʂɑJ�ڂ���̂�
    bool transition;

public:

    //�R���X�g���N�^
    StageSelect();

    //�f�X�g���N�^
    ~StageSelect();

    //�`��ȊO�̍X�V����������
    void Update(Key* key) override;

    //�`��Ɋւ��邱�Ƃ���������
    void Draw() const override;

    //�V�[���؂�ւ�
    AbstractScene* ChangeScene() override;

};

