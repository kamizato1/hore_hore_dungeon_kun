#include "Pause.h"

#define INPUT_ACCEPTANCE_TIME 60

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
			select_menu = (select_menu - 1 + static_cast<int>(MENU::MENU_SIZE)) % static_cast<int>(MENU::MENU_SIZE);
		}
		else if (key->GetStickAngle(L).y < 0)
		{
			select_menu = (select_menu + 1) % static_cast<int>(MENU::MENU_SIZE);
		}
	}
}

//-----------------------------------
// 描画
//-----------------------------------
void Pause::Draw() const
{

}

//-----------------------------------
// 値を参照させるため
//-----------------------------------
bool Pause::GetNextScene()
{
	return next_scene;
}
