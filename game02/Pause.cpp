#include "Pause.h"
#include "DxLib.h"

#define INPUT_ACCEPTANCE_TIME 30

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Pause::Pause()
{
	input_time = 0;
	cursor_y = 0;
	select_menu = static_cast<int>(MENU::GAME_START);
	next_scene = false;

}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Pause::~Pause()
{

}

//-----------------------------------
// �X�V
//-----------------------------------
void Pause::Update(Key* key)
{
	if (key->KeyDown(B))
	{
		next_scene = true;
	}

	if (++input_time > INPUT_ACCEPTANCE_TIME)
	{
		if (key->GetStickAngle(L).y > 0)
		{
			select_menu = (select_menu + 1) % static_cast<int>(MENU::MENU_SIZE);
		}
		else if (key->GetStickAngle(L).y < 0)
		{
			select_menu = (select_menu - 1 + static_cast<int>(MENU::MENU_SIZE)) % static_cast<int>(MENU::MENU_SIZE);
		}
		input_time = 0;
	}

	switch (select_menu)
	{
	case 0:
		cursor_y = 200;
		break;
	case 1:
		cursor_y = 300;
		break;
	case 2:
		cursor_y = 400;
		break;
	default:
		break;
	}
}

//-----------------------------------
// �`��
//-----------------------------------
void Pause::Draw() const
{

	DrawString(190, 200, "GAMESTATE�I", 0xffffff);

	DrawString(190, 300, "TITLE", 0xffffff);

	DrawString(190, 400, "GAMEEND", 0xffffff);

	DrawString(175, cursor_y, "��", 0xffffff);

	DrawFormatString(0, 500, 0xffffff, "%d", select_menu);

}

//-----------------------------------
// �l�ύX
//-----------------------------------
void Pause::SetNextScene()
{
	next_scene = false;
}

//-----------------------------------
// �l�Q��
//-----------------------------------
int Pause::GetSelectMenu()
{
	return select_menu;
}

//-----------------------------------
// �l���Q�Ƃ����邽��
//-----------------------------------
bool Pause::GetNextScene()
{
	return next_scene;
}
