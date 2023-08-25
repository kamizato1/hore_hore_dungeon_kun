#include "Pause.h"
#include "DxLib.h"

#define INPUT_ACCEPTANCE_TIME 30

//-----------------------------------
// コンストラクタ
//-----------------------------------
Pause::Pause()
{
	input_time = 0;
	cursor_y = 0;
	select_menu = static_cast<int>(MENU::GAME_START);
	next_scene = false;

}

//-----------------------------------
// デストラクタ
//-----------------------------------
Pause::~Pause()
{

}

//-----------------------------------
// 更新
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
// 描画
//-----------------------------------
void Pause::Draw() const
{

	DrawString(190, 200, "GAMESTATE！", 0xffffff);

	DrawString(190, 300, "TITLE", 0xffffff);

	DrawString(190, 400, "GAMEEND", 0xffffff);

	DrawString(175, cursor_y, "■", 0xffffff);

	DrawFormatString(0, 500, 0xffffff, "%d", select_menu);

}

//-----------------------------------
// 値変更
//-----------------------------------
void Pause::SetNextScene()
{
	next_scene = false;
}

//-----------------------------------
// 値参照
//-----------------------------------
int Pause::GetSelectMenu()
{
	return select_menu;
}

//-----------------------------------
// 値を参照させるため
//-----------------------------------
bool Pause::GetNextScene()
{
	return next_scene;
}
