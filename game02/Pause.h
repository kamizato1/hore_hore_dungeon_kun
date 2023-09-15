#pragma once
#include"Key.h"

class Pause
{
private:

    int select_se;
    int decision_se;
    int return_se;

    int input_time; //���͎�t����
    int select_menu_num; // ���ݓ��͂��Ă��郁�j���[
    bool select_menu_decision;
    int answer_num;
    bool answer_decision;

    int menu_image[4][2]; //�摜
    int answer_image[2][2]; //�ŏI�m�F�摜
    int text_image[3];
    int help_image[3];
    int number_image[4];
    int back_ground_image; //�w�i��
    int pause_image;

    int set_menu_image[8]; //�摜
    int set_answer_image[4]; //�ŏI�m�F�摜

    int help_num;
    int change_scene;
    bool can_close;

public:

    
    Pause();//�R���X�g���N�^
    void Delete();

    bool Update(Key* key);//�`��ȊO�̍X�V����������
    void Draw() const;//�`��Ɋւ��邱�Ƃ���������
    
    void MenuUpdate(Key* key);
    void TextUpdate(Key* key);

    void Init();

    int GetChangeScene() { return change_scene; }

};

