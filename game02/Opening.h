#pragma once
#include "AbstractScene.h"
class Opening :
    public AbstractScene
{
private:

    //�A�j���[�V����
    int animation;

    //�A�j���[�V��������
    int animation_time;

    //�\������
    int display_time;

    //�o�ߎ���
    int time;

    //���݂̎��ŋ�
    int story_no;

    //�摜   
    int image[5];

    //�����摜
    int character_image[5];

    int background_image;

    //���邳
    int brightness;

    //���̃V�[���ɍs����̂�
    bool can_scene_change;

public:

    //�R���X�g���N�^
    Opening();

    ////�f�X�g���N�^
    ~Opening();

    //�`��ȊO�̍X�V����������
    void Update(Key* key) override;

    //�`��Ɋւ��邱�Ƃ���������
    void Draw() const override;

    //�V�[���؂�ւ�
    AbstractScene* ChangeScene() override;

};

