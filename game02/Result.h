#pragma once
#include "AbstractScene.h"
class Result :
    public AbstractScene
{
private:

    //�X�R�A
    int score;

public:

    
    //�R���X�g���N�^
    Result(int block_break,int time );//�󂵂��u���b�N�̐��A���ԁA�����Ă���u���b�N�̐�,��̎�ނƎ��

    //�f�X�g���N�^
    ~Result();

    //�`��ȊO�̍X�V����������
    void Update(Key* key) override;

    //�`��Ɋւ��邱�Ƃ���������
    void Draw() const override;

    //�V�[���؂�ւ�
    AbstractScene* ChangeScene() override;

};

