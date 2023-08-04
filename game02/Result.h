#pragma once
#include "AbstractScene.h"
#include "define.h"

class Result :
    public AbstractScene
{
private:

    int score; //�X�R�A

    TREASURE_TYPE treasure; //�������Ă����A�C�e����ۑ�����B

    int time; //�c�莞�Ԃ��i�[����B

    int block_break; //�j�󂵂��u���b�N�̐�

    int block; //�������Ă����u���b�N�̐��i�������A�C�e���j

public:

    
    //�R���X�g���N�^
    Result(int block_break,int time, int block, TREASURE_TYPE treasure);//�󂵂��u���b�N�̐��A���ԁA�����Ă���u���b�N�̐�,��̎�ނƎ��

    //�f�X�g���N�^
    ~Result();

    //�`��ȊO�̍X�V����������
    void Update(Key* key) override;

    //�`��Ɋւ��邱�Ƃ���������
    void Draw() const override;

    //�V�[���؂�ւ�
    AbstractScene* ChangeScene() override;

};

