#pragma once

#include"AbstractScene.h"
#include"Key.h"
#include"define.h"

class Title : public AbstractScene
{
private:

    int image; //�w�i�摜
    int cursor_image;  //�J�[�\���摜
    int cursor_y;   //�J�[�\���ʒu
    int input_time; //���͎�t����
    int select_menu; // ���ݓ��͂��Ă��郁�j���[
    bool can_scene_change; //���̃V�[���ɍs���邩
    

    enum class MENU
    {
        GAME_START,
        HELP,
        RANKING,
        CLEDIT,
        END,
        MENU_SIZE
    };

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