#include"DxLib.h"
#include"Title.h"
#include"GameMain.h"

#define  INPUT_ACCEPTANCE_TIME 60

//-----------------------------------
// コンストラクタ
//-----------------------------------
Title::Title()
{
	input_time = 0;
	cursor_y = 0;
	select_menu = static_cast<int>(MENU::GAME_START);
	can_scene_change = FALSE;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Title::~Title()
{

}


//-----------------------------------
// 更新
//-----------------------------------
void Title::Update(Key* key)
{

	if (key->KeyDown(B))
	{
		can_scene_change = TRUE;
	}

	if (++input_time > INPUT_ACCEPTANCE_TIME)
	{
		if (key->GetStickAngle(L).y < 0)
		{
			select_menu = (select_menu - 1 + static_cast<int>(MENU::MENU_SIZE)) % static_cast<int>(MENU::MENU_SIZE);
		}
		else if (key->GetStickAngle(L).y > 0)
		{
			select_menu = (select_menu + 1) % static_cast<int>(MENU::MENU_SIZE);
		}
	}

}


//-----------------------------------
// 描画
//-----------------------------------
void Title::Draw() const
{
	SetFontSize(30);

	DrawString(190, 200, "惚れ掘れダンジョン君！", 0xffffff);

	DrawString(190, 300, "Bボタンを押そう！", 0xffffff);
}


//-----------------------------------
// 遷移
//-----------------------------------
AbstractScene* Title::ChangeScene()
{

	if (can_scene_change)
	{
		return new GameMain(); //次の遷移
	}

	return this;
}