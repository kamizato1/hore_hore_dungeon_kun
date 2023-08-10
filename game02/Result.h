#pragma once
#include "AbstractScene.h"
class Result :
    public AbstractScene
{
private:

    //�X�R�A
    int score;

    //�摜
    int image;

    //�J�ڂ���̂�
    bool transition;

public:

    
    //�R���X�g���N�^
    Result(int block_break,int time ,int item_block);//�󂵂��u���b�N�̐��A���ԁA�����Ă���u���b�N�̐�,��̎�ނƎ��

    //�f�X�g���N�^
    ~Result();

    //�`��ȊO�̍X�V����������
    void Update(Key* key) override;

    //�`��Ɋւ��邱�Ƃ���������
    void Draw() const override;

    //�V�[���؂�ւ�
    AbstractScene* ChangeScene() override;

};

