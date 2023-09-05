#pragma once
#include "AbstractScene.h"

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
    int player_image[4]; //�v���C���[�摜
    int type_image; //�摜�C���[�W

    //�J�[�\���̍��W
    float cursor_x;
    float cursor_y;

    float player_x;
    float player_y;

    

    //���̉�ʂɑJ�ڂ���̂�
    bool transition;

    //�����Ă������
    bool direction;

public:

    //�R���X�g���N�^
    StageSelect(int stage_num);

    //�f�X�g���N�^
    ~StageSelect();

    //�`��ȊO�̍X�V����������
    void Update(Key* key) override;

    //�`��Ɋւ��邱�Ƃ���������
    void Draw() const override;

    //�V�[���؂�ւ�
    AbstractScene* ChangeScene() override;

};

