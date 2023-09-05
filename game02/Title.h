#pragma once

#include"AbstractScene.h"
#include"Key.h"
#include"define.h"

#define MENU_NUM 4

class Title : public AbstractScene
{
private:

    int image; //�w�i�摜
    int menu_image[MENU_NUM][2]; //���j���[�摜

    int input_time; //���͎�t����
    int select_menu; // ���ݓ��͂��Ă��郁�j���[
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