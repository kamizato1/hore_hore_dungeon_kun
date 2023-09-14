#include "Pause.h"
#include "DxLib.h"

#define INPUT_ACCEPTANCE_TIME 30

//-----------------------------------
// コンストラクタ
//-----------------------------------
Pause::Pause()
{
	decision_se = LoadSoundMem("bgm/click.mp3");
	select_se = LoadSoundMem("bgm/MoveCursor.mp3");
	
	back_ground_image = LoadGraph("images/Pause/map.png");
	LoadDivGraph("images/Pause/help.png", 3, 3, 1, 1000, 700, help_image);
	LoadDivGraph("images/Pause/number.png", 4, 4, 1, 140, 150, number_image);
	pause_image = LoadGraph("images/Pause/pause.png");
	int menu_image[8];
	int count = 0;
	LoadDivGraph("images/Pause/menu.png", 8, 2, 4, 630, 90, menu_image);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)this->menu_image[i][j] = menu_image[count++];
	}
	int answer_image[4];
	count = 0;
	LoadDivGraph("images/Pause/answer.png", 4, 2, 2, 288, 90, answer_image);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)this->answer_image[i][j] = answer_image[count++];
	}
	LoadDivGraph("images/Pause/text.png", 3, 1, 3, 750, 60, text_image);
}

void Pause::Init()
{
	input_time = INPUT_ACCEPTANCE_TIME;
	select_menu_num = 0;
	select_menu_decision = FALSE;
	answer_num = 0;
	answer_decision = FALSE;
	can_close = FALSE;
	change_scene = 0;
	help_num = 0;
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
bool Pause::Update(Key* key)
{
	if (!select_menu_decision)MenuUpdate(key);
	else TextUpdate(key);

	return can_close;
}

void Pause::MenuUpdate(Key* key)
{
	//スティックを動かしたら
	if (key->GetStickAngle(L).y == 0)input_time = 0;
	else if (--input_time < 0)input_time = 0;

	//操作受け
	if (input_time == 0)
	{
		if (key->GetStickAngle(L).y > 0)
		{
			if (++select_menu_num > 3)select_menu_num = 0;
			input_time = INPUT_ACCEPTANCE_TIME;
			PlaySoundMem(select_se, DX_PLAYTYPE_BACK, TRUE);
		}
		else if (key->GetStickAngle(L).y < 0)
		{
			if (--select_menu_num < 0)select_menu_num = 3;
			input_time = INPUT_ACCEPTANCE_TIME;
			PlaySoundMem(select_se, DX_PLAYTYPE_BACK, TRUE);
		}
	}

	if (key->KeyDown(B))
	{
		select_menu_decision = TRUE;
		if (select_menu_num == 0)can_close = TRUE;
		PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE);
	}
	else if(key->KeyDown(A))can_close = TRUE;
}

void Pause::TextUpdate(Key* key)
{
	int select_num = 1;
	if(select_menu_num == 3)select_num = 2;

	if (key->GetStickAngle(L).x == 0)input_time = 0;
	else if (--input_time < 0)input_time = 0;

	//操作受け
	if (input_time == 0)
	{
		if (key->GetStickAngle(L).x > 0)
		{
			if (++answer_num > select_num)answer_num = 0;
			input_time = INPUT_ACCEPTANCE_TIME;
			PlaySoundMem(select_se, DX_PLAYTYPE_BACK, TRUE);
		}
		else if (key->GetStickAngle(L).x < 0)
		{
			if (--answer_num < 0)answer_num = select_num;
			input_time = INPUT_ACCEPTANCE_TIME;
			PlaySoundMem(select_se, DX_PLAYTYPE_BACK, TRUE);
		}
	}

	if (key->KeyDown(B))
	{
		if (select_menu_num != 3)
		{
			if (answer_num == 0)change_scene = select_menu_num;
			else select_menu_decision = FALSE, answer_num = 0;
			PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE);
		}
		
	}
	else if (key->KeyDown(A))select_menu_decision = FALSE, answer_num = 0;
}

//-----------------------------------
// 描画
//-----------------------------------
void Pause::Draw() const
{

	DrawRotaGraph(640, 360, 1, 0, back_ground_image, TRUE);
	DrawRotaGraph(640, 110, 1, 0, pause_image, TRUE);

	if (!select_menu_decision)
	{
		
		for (int i = 0; i < 4; i++)
		{
			bool flg = FALSE;
			if (i == select_menu_num)flg = TRUE;
			DrawRotaGraph(640, 240 + (i * 100), 1, 0, menu_image[i][flg], TRUE);
		}
	}
	else
	{
		if (select_menu_num == 3)
		{
			DrawRotaGraph(640, 360, 1, 0, help_image[answer_num], TRUE);
			DrawRotaGraph(890, 90, 0.3, 0, number_image[0], TRUE, TRUE);
			DrawRotaGraph(970, 90, 0.3, 0, number_image[answer_num + 1], TRUE);
			DrawRotaGraph(1050, 90, 0.3, 0, number_image[0], TRUE);
		}
		else
		{
			DrawRotaGraph(640, 240, 1, 0, text_image[select_menu_num], TRUE);
			DrawRotaGraph(640, 340, 1, 0, text_image[0], TRUE);

			for (int i = 0; i < 2; i++)
			{
				bool flg = FALSE;
				if (i == answer_num)flg = TRUE;
				DrawRotaGraph(430 + (i * 400), 500, 1, 0, answer_image[i][flg], TRUE);
			}
		}
		
	}

}



