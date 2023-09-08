#include"DxLib.h"
#include"Title.h"
#include"StageSelect.h"
#include"GameMain.h"

#define  INPUT_ACCEPTANCE_TIME 10

//-----------------------------------
// コンストラクタ
//-----------------------------------
Title::Title()
{
	input_time = 0;
	can_scene_change = FALSE;
	select_menu = 0;
	image = LoadGraph("images/Title.png");
	int menu_image[8];
	LoadDivGraph("images/Menu/menu.png", 8, 2, 4, 600, 100, menu_image);
	int count = 0;
	for (int i = 0; i < MENU_NUM; i++)
	{
		for (int j = 0; j < 2; j++)this->menu_image[i][j] = menu_image[count++];
	}
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
	//ボタンが押されたら
	if (key->KeyDown(B))can_scene_change = TRUE;

	//入力受付るのか
	if (++input_time > INPUT_ACCEPTANCE_TIME)
	{
		if (key->GetStickAngle(L).y > 0)
		{
			if (++select_menu == MENU_NUM)select_menu = 0;
			input_time = 0;
		}
		else if (key->GetStickAngle(L).y < 0)
		{
			if (--select_menu < 0)select_menu = MENU_NUM - 1;
			input_time = 0;
		}
	}

}

//-----------------------------------
// 描画
//-----------------------------------
void Title::Draw() const
{
	//背景画像
	DrawGraph(0, 0, image, false);

	for (int i = 0; i < MENU_NUM; i++)
	{
		bool flg = FALSE;
		if (i == select_menu)flg = TRUE;

		DrawRotaGraph(1010, 250 + (i * 100), 1, 0, menu_image[i][flg], TRUE);
	}
}

//-----------------------------------
// 遷移
//-----------------------------------
AbstractScene* Title::ChangeScene()
{
	//ボタンが押されたら
	if (can_scene_change)
	{
		switch (select_menu)
		{
		case 0: //ゲームメインに遷移
			return new StageSelect(1);
			break;
		case 1:
			//return new herupu
			break;
		case 2:
			//return new rannking
			break;

		case 3:
			//return new クレジット
			break;

		case 4: //ゲーム終了
			return nullptr;
			break;
		}
	}

	return this;
}