#pragma once
#include "AbstractScene.h"
class Help :
    public AbstractScene
{
private:

    int image; //�摜
    int flashing_time; //�����`�掞��

    bool chane_title; //�^�C�g���ɑJ�ڂ���̂�

public:
    
    //�R���X�g���N�^
    Help();
    
    //�`��ȊO�̍X�V����������
    void Update(Key* key) override;

    //�`��Ɋւ��邱�Ƃ���������
    void Draw() const override;

    //�V�[���؂�ւ�
    AbstractScene* ChangeScene() override;

};

