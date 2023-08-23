#pragma once
#include"Key.h"

class Pause
{
private:

    //���j���ꗗ
    enum class MENU
    {
        GAME_START,
        TITLE,
        END,
        MENU_SIZE
    };

    int cursor_image;  //�J�[�\���摜
    int cursor_y;   //�J�[�\���ʒu
    int input_time; //���͎�t����
    int select_menu; // ���ݓ��͂��Ă��郁�j���[

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

    //�l�Q��
    int GetSelectMenu();
   
    //�l�Q��
    bool GetNextScene();

};

