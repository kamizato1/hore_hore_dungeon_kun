#include "Pause.h"

#define INPUT_ACCEPTANCE_TIME 60

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
void Pause::Draw() const
{

}

//-----------------------------------
// �l���Q�Ƃ����邽��
//-----------------------------------
bool Pause::GetNextScene()
{
	return next_scene;
}
