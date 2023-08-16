#include"DxLib.h"
#include"Title.h"
#include"GameMain.h"

#define INPUT_ACCEPTANCE_TIME 60

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Title::Title()
{
    flashing_time = 0;
    input_time = 0;
    cursor_y = 0;

    can_scene_change = FALSE;

    select_menu = static_cast<int>(MENU::GAME_START); 
    
    image = LoadGraph("images/home.png");
    imgae1 = LoadGraph("images/start.png");
    cursor_image = LoadGraph("images/triangle.png");
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
    input_time++;

    flashing_time++;

    if (flashing_time >= 60)
    {
        flashing_time = 0;
    }

    if (key->KeyDown(B))
    {
        can_scene_change = TRUE;
    }

    //�������ŃJ�[�\�����ړ����Ȃ��悤�ɂ���
    if (++input_time > INPUT_ACCEPTANCE_TIME)
    {
        if (key->GetStickAngle(L).y > 0)
        {
            select_menu = (select_menu - 1 + static_cast<int>(MENU::MENU_SIZE)) % static_cast<int>(MENU::MENU_SIZE);
        }
        else if (key->GetStickAngle(L).y < 0)
        {
            select_menu = (select_menu + 1) % static_cast<int>(MENU::MENU_SIZE);
        }
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


    DrawGraph(0, 0, image, false);
    DrawGraph(715, 250, imgae1, true);

    DrawFormatString(100, 100, 0xFFFFFF, "%d ", select_menu);

   // //�J�[�\���ʒu
    //DrawTriangle(745, 280, 700, 240, 700, 320, GetColor(250, 0, 0), TRUE);
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