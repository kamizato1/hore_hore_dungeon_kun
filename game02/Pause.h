#pragma once
#include"Key.h"

class Pause
{
private:

    int input_time; //���͎�t����
    int select_menu_num; // ���ݓ��͂��Ă��郁�j���[
    bool select_menu_decision;
    int answer_num;
    bool answer_decision;

    int menu_image[4][2]; //�摜
    int answer_image[2][2]; //�ŏI�m�F�摜
    int text_image[3];
    int help_image;
    int back_ground_image; //�w�i��
    int pause_image;

    int change_scene;

    bool can_close;

public:

    
    Pause();//�R���X�g���N�^
    ~Pause(); //�f�X�g���N�^

    bool Update(Key* key);//�`��ȊO�̍X�V����������
    void Draw() const;//�`��Ɋւ��邱�Ƃ���������
    
    void MenuUpdate(Key* key);
    void TextUpdate(Key* key);

    void Init();

    int GetChangeScene() { return change_scene; }

};

