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
	cursor_x = 0;
	select_menu = static_cast<int>(MENU::TITLE);
	confirmation_menu = static_cast<int>(SELECTION::NO);
	next_scene = false;
	confirmation = false;

	image[0] = LoadGraph("images/Pause/はい.png");
	image[1] = LoadGraph("images/Pause/いいえ.png");
	image[2] = LoadGraph("images/Pause/ゲームスタート.png"); //いる？
	image[3] = LoadGraph("images/Pause/タイトル.png");
	image[4] = LoadGraph("images/Pause/ステージセレクト.png");
	image[5] = LoadGraph("images/Pause/ステージセレクトに戻りますか？.png");
	image[6] = LoadGraph("images/Pause/ヘルプ.png");
	image[7] = LoadGraph("images/Pause/リスタート.png");
	image[8] = LoadGraph("images/Pause/取った宝は失われます。.png");
	image[9] = LoadGraph("images/Pause/諦める.png");
	image[10] = LoadGraph("images/Pause/ゲーム終了.png");

	image1[0] = LoadGraph("images/Pause/タイトル.png");
	image1[1] = LoadGraph("images/Pause/ステージセレクトに戻りますか？.png");
	//image1[2];ヘルプ画像？
	image1[3] = LoadGraph("images/Pause/諦める.png");
	image1[4] = LoadGraph("images/Pause/取った宝は失われます。.png");


	background= LoadGraph("images/Pause/背景.png");

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

	if (confirmation)
	{
		if (++input_time > INPUT_ACCEPTANCE_TIME)
		{
			if (key->GetStickAngle(L).x > 0)
			{
				confirmation_menu = (confirmation_menu + 1) % static_cast<int>(SELECTION::MENU_SIZE);
			}
			else if (key->GetStickAngle(L).x < 0)
			{
				confirmation_menu = (confirmation_menu - 1 + static_cast<int>(SELECTION::MENU_SIZE)) % static_cast<int>(SELECTION::MENU_SIZE);
			}
			input_time = 0;
		}

		cursor_y = 400;
		switch (confirmation_menu)
		{
		case 0:
			cursor_x = 300;
			break;
		case 1:
			cursor_x = 700;
			break;

		default:
			break;
		}

		if (key->KeyDown(B) && confirmation_menu == 1)
		{
			confirmation = false;
		}
		else if (key->KeyDown(B) && confirmation_menu == 0)
		{
			next_scene = true;
		}

	}
	else
	{
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


		if (key->KeyDown(B))
		{
			confirmation = true;
		}
		cursor_x = 400;
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
		case 3:
			cursor_y = 500;
			break;
		default:
			break;
		}

	}



}

//-----------------------------------
// 描画
//-----------------------------------
void Pause::Draw() const
{

	DrawRotaGraph(630, 360, 1, 0, background, false);

	if (confirmation)
	{
		DrawRotaGraph(600, 200, 0.6f, 0, image1[select_menu], TRUE);

		DrawRotaGraph(600, 300, 0.6f, 0, image1[4], TRUE);

		DrawRotaGraph(430, 400, 0.6f, 0, image[0], TRUE); //はい
		DrawRotaGraph(830, 400, 0.6f, 0, image[1], TRUE); //いいえ

		DrawFormatString(0, 500, 0xffffff, "%d", confirmation_menu);

		DrawString(cursor_x, cursor_y, "■", 0xffffff);

	}
	
	else
	{

		DrawString(cursor_x, cursor_y, "■", 0xffffff);

		DrawRotaGraph(600, 200, 0.6, 0, image[3], TRUE); //タイトル

		DrawRotaGraph(730, 300, 0.6f, 0, image[4], TRUE); //ステージセレクト

		DrawRotaGraph(570, 400, 0.6f, 0, image[6], TRUE); //ヘルプ

		DrawRotaGraph(630, 500, 0.6f, 0, image[10], TRUE); //ゲーム終了

		DrawFormatString(0, 500, 0xffffff, "%d", select_menu);

	}


}

//-----------------------------------
// 値変更
//-----------------------------------
void Pause::SetNextScene()
{
	next_scene = false;
}

void Pause::Setconfirmation()
{
	confirmation = false;
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
