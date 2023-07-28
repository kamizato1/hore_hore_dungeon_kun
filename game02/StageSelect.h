#pragma once
#include "AbstractScene.h"


//�X�e�[�W�Z���N�g��ʂɂ��āi�R�X�e�[�W�j
//New �X�[�p�[�}���I�u���U�[�Y�̃X�e�[�W�I����ʂ��Q�l�ɂ���B



class StageSelect :
    public AbstractScene
{
private:

    //���ݑI�𒆂̃X�e�[�W�ԍ�
    int stage_number;

    

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

