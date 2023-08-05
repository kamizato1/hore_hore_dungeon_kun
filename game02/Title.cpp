#include"DxLib.h"
#include"Title.h"
#include"GameMain.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Title::Title()
{
    flashing_time = 0;
    push_time = 0;
    can_scene_change = FALSE;
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Title::~Title()
{

}


//-----------------------------------
// �X�V
//-----------------------------------
void Title::Update(Key* key)
{
    push_time++;

    flashing_time++;

    if (flashing_time >= 60)
    {
        flashing_time = 0;
    }

    if (key->KeyDown(B) && push_time >= 30)
    {
        can_scene_change = TRUE;
    }
}


//-----------------------------------
// �`��
//-----------------------------------
void Title::Draw() const
{
    SetFontSize(30);

    DrawString(190, 200, "����@��_���W�����N�I", 0xffffff);
    
    if (flashing_time / 30 == 0)
    {
        DrawString(190, 300, "B�{�^�����������I", 0xffffff);
    }
}


//-----------------------------------
// �J��
//-----------------------------------
AbstractScene* Title::ChangeScene()
{
    if (can_scene_change)
    {
        return new GameMain(); //���̑J��
    }

    return this;
}