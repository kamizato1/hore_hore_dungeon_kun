#pragma once

#include"AbstractScene.h"
#include"Key.h"
#include"define.h"

#define MENU_NUM 4

class Title : public AbstractScene
{
private:

    int image; //�w�i�摜
    int help_image[3]; //�w���v�C���[�W
    int credit_image; //�N���W�b�g���
    int menu_image[MENU_NUM][2]; //���j���[�摜
    int num_image[10];
    int slash_image;
    int input_time; //���͎�t����
    int select_menu; // ���ݓ��͂��Ă��郁�j���[
    int bgm; //BGM
    int move_se; //�����Ƃ���SE
    int decision_se; //����I��
    int help_menu; //�w���v���j��


    bool can_scene_change; //���̃V�[���ɍs���邩
    bool help; //�w���v��ʊJ���̂�
    bool credit; //�N���W�b�g

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