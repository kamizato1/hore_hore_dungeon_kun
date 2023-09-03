#include"DxLib.h"
#include"Title.h"
#include"GameMain.h"

#define  INPUT_ACCEPTANCE_TIME 10

//-----------------------------------
// コンストラクタ
//-----------------------------------
Title::Title()
{
	input_time = 0;
	cursor_y = 0;
	select_menu = static_cast<int>(MENU_NAME::GAME_START);
	can_scene_change = FALSE;

	image = LoadGraph("images/home.png");

	//メニュー画像 (選択されている状態)
	mene[0].image = LoadGraph("images/Menu/start.png");
	mene[0].x = 1010;
	mene[0].y = 250;

	mene[1].image = LoadGraph("images/Menu/help.png");
	mene[1].x = 1010;
	mene[1].y = 350;

	mene[2].image = LoadGraph("images/Menu/ranking.png");
	mene[2].x = 1010;
	mene[2].y = 450;

	mene[3].image = LoadGraph("images/Menu/cledit.png");
	mene[3].x = 1010;
	mene[3].y = 550;

	mene[4].image = LoadGraph("images/Menu/end.png");
	mene[4].x = 1010;
	mene[4].y = 650;

	//メニュー画像（選択されていない状態）
	mene[5].image = LoadGraph("images/Menu/start2.png");
	mene[5].x = 1010;
	mene[5].y = 250;

	mene[6].image = LoadGraph("images/Menu/help2.png");
	mene[6].x = 1010;
	mene[6].y = 350;

	mene[7].image = LoadGraph("images/Menu/ranking2.png");
	mene[7].x = 1010;
	mene[7].y = 450;

	mene[8].image = LoadGraph("images/Menu/cledit2.png");
	mene[8].x = 1010;
	mene[8].y = 550;

	mene[9].image = LoadGraph("images/Menu/end2.png");
	mene[9].x = 1010;
	mene[9].y = 650;

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
	if (key->KeyDown(B))
	{
		can_scene_change = TRUE;
	}

	//入力受付るのか
	if (++input_time > INPUT_ACCEPTANCE_TIME)
	{
		if (key->GetStickAngle(L).y > 0)
		{
			select_menu = (select_menu + 1) % static_cast<int>(MENU_NAME::MENU_SIZE);
			input_time = 0;
		}
		else if (key->GetStickAngle(L).y < 0)
		{
			select_menu = (select_menu - 1 + static_cast<int>(MENU_NAME::MENU_SIZE)) % static_cast<int>(MENU_NAME::MENU_SIZE);
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

	//通常状態の画像
	for (int  i = 5; i < 10; i++)
	{
		DrawRotaGraph(mene[i].x, mene[i].y, 0.9f, 0, mene[i].image, TRUE);
	}

	//選択しているメニュー画像（赤い）を表にだす。
	switch (select_menu)
	{
	case 0:
		DrawRotaGraph(mene[0].x, mene[0].y, 0.9f, 0, mene[0].image, TRUE);
		break;
	case 1:
		DrawRotaGraph(mene[1].x, mene[1].y, 0.9f, 0, mene[1].image, TRUE);
		break;
	case 2:
		DrawRotaGraph(mene[2].x, mene[2].y, 0.9f, 0, mene[2].image, TRUE);
		break;

	case 3:
		DrawRotaGraph(mene[3].x, mene[3].y, 0.9f, 0, mene[3].image, TRUE);
		break;

	case 4:
		DrawRotaGraph(mene[4].x, mene[4].y, 0.9f, 0, mene[4].image, TRUE);
		break;
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
			//return new GameMain();
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