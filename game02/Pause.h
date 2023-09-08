#pragma once
#include"Key.h"

class Pause
{
private:

    //���j���ꗗ
    enum class MENU
    {
        TITLE,
        STAGE_SELECT,
        HELP,
        END,
        MENU_SIZE
    };

    //�ŏI����
    enum class SELECTION
    {
        YES,
        NO,
        MENU_SIZE
    };

    int cursor_image;  //�J�[�\���摜
    int cursor_y;   //�J�[�\���ʒu
    int cursor_x;  //�J�[�\���ʒu
    int input_time; //���͎�t����
    int select_menu; // ���ݓ��͂��Ă��郁�j���[
    int confirmation_menu; //���ݓ��͂��Ă��郁�j���[

    int image[11]; //�摜
    int image1[5]; //�ŏI�m�F�摜
    int background; //�w�i��


    bool confirmation; //�m�F���

    bool next_scene; //���̃V�[��

public:

    //�R���X�g���N�^
    Pause();

    //�f�X�g���N�^
    ~Pause();

    //�`��ȊO�̍X�V����������
    void Update(Key* key);

    //�`��Ɋւ��邱�Ƃ���������
    void Draw() const;
    
    //�l�ύX
    void SetNextScene();
    void Setconfirmation();

    //�l�Q��
    int GetSelectMenu();
   
    //�l�Q��
    bool GetNextScene();

};

