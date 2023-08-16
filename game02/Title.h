#pragma once

#include"AbstractScene.h"
#include"Key.h"
#include"define.h"

class Title : public AbstractScene
{
private:

    //�e�X�g
    int image;
    int imgae1;
    //�e�X�g

    int flashing_time; //�����_�Ŏ���
    int push_time; // �Q�[�����C���ɍs����悤�ɂȂ�܂ł̎���
    bool can_scene_change; //���̃V�[���ɍs���邩


public:

    //�R���X�g���N�^
    Title();

    ////�f�X�g���N�^
    ~Title();

    //�`��ȊO�̍X�V����������
    void Update(Key* key) override;

    //�`��Ɋւ��邱�Ƃ���������
    void Draw() const override;

    //�V�[���؂�ւ�
    AbstractScene* ChangeScene() override;

};