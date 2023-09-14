#pragma once
#include "AbstractScene.h"

//�X�e�[�W�Z���N�g��ʂɂ��āi�R�X�e�[�W�j
//New �X�[�p�[�}���I�u���U�[�Y�̃X�e�[�W�I����ʂ��Q�l�ɂ���B

class StageSelect : public AbstractScene
{
private:

    int select_se;
    int decision_se;
    int stage_select_bgm;

    int wait_time;

    int stage_number;//���ݑI�𒆂̃X�e�[�W�ԍ�
    int stage_score[STAGE_NUM];
    int number_image[10];
    int operating_time;//�����t
    int back_ground_image[5];//�w�i�摜
    int background_image;//�w�i�摜
    int player_image[4]; //�v���C���[�摜
    int player_image_type; //�摜�C���[�W
    int player_image_change_time;
    int clear_stage; //�N���A�X�e�[�W
    DATA player_location[STAGE_NUM];
    bool transition;//���̉�ʂɑJ�ڂ���̂�
    bool title; //�^�C�g���߂�
 
public:

    
    StageSelect(int stage_num);//�R���X�g���N�^
    ~StageSelect();//�f�X�g���N�^

    void Update(Key* key) override;//�`��ȊO�̍X�V����������
    void Draw() const override;//�`��Ɋւ��邱�Ƃ���������

    AbstractScene* ChangeScene() override; //�V�[���؂�ւ�
};

