#include"DxLib.h"
#include"Title.h"
#include"StageSelect.h"
#include"Opening.h"
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
	bgm = LoadSoundMem("bgm/Title.mp3");
	help = false;
	int count = 0;
	for (int i = 0; i < MENU_NUM; i++)
	{
		for (int j = 0; j < 2; j++)this->menu_image[i][j] = menu_image[count++];
	}
	help_menu = 0;

	credit = false;

	decision_se = LoadSoundMem("bgm/Click.mp3");
	move_se = LoadSoundMem("bgm/MoveCursor.mp3");

	help_image[0] = LoadGraph("images/Menu/help.png");
	help_image[1] = LoadGraph("images/Menu/map (2).png");
	help_image[2] = LoadGraph("images/Menu/map (3).png");

	credit_image = LoadGraph("images/Menu/map.png");

	LoadDivGraph("images/Ui/number.png", 10, 10, 1, 20, 40, num_image);
	LoadDivGraph("images/Ui/sign.png", 2, 2, 1, 20, 40, slash_image);
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

	if (CheckSoundMem(bgm) != 1) {   //SEが流れていなかったら再生
		ChangeVolumeSoundMem(255 * 40 / 100, bgm); //SE音量調整 255最大音量から80%再生
		PlaySoundMem(bgm, DX_PLAYTYPE_BACK, TRUE); //SE再生
	}

	//ボタンが押されたら

	if (credit == false && help == false)
	{

		if (key->KeyDown(B) && select_menu == 1)
		{
			help = true;
			ChangeVolumeSoundMem(255 * 40 / 100, decision_se); //SE音量調整 255最大音量から80%再生
			PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE); //SE再生
		}

		else if (key->KeyDown(B) && select_menu == 2)
		{
			credit = true;
			ChangeVolumeSoundMem(255 * 40 / 100, decision_se); //SE音量調整 255最大音量から80%再生
			PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE); //SE再生
		}

		else if (key->KeyDown(B))
		{
			ChangeVolumeSoundMem(255 * 40 / 100, decision_se); //SE音量調整 255最大音量から80%再生
			PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE); //SE再生
			can_scene_change = TRUE;
		}

	}
	if (help)
	{

		if (++input_time > INPUT_ACCEPTANCE_TIME)
		{
			if (key->GetStickAngle(L).x > 0)
			{

				ChangeVolumeSoundMem(255 * 40 / 100, move_se); //SE音量調整 255最大音量から80%再生
				PlaySoundMem(move_se, DX_PLAYTYPE_BACK, TRUE); //SE再生

				if (++help_menu == 3)help_menu = 0;
				input_time = 1;
			}
			else if (key->GetStickAngle(L).x < 0)
			{

				ChangeVolumeSoundMem(255 * 40 / 100, move_se); //SE音量調整 255最大音量から80%再生
				PlaySoundMem(move_se, DX_PLAYTYPE_BACK, TRUE); //SE再生

				if (--help_menu < 0)help_menu = 2;
				input_time = 1;
			}
		}

		if (key->KeyDown(A))
		{
			ChangeVolumeSoundMem(255 * 40 / 100, decision_se); //SE音量調整 255最大音量から80%再生
			PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE); //SE再生
			input_time = 1;
			help_menu = 0;
			help = false;
		}

	}

	else if(credit)
	{

		if (key->KeyDown(A))
		{
			ChangeVolumeSoundMem(255 * 40 / 100, decision_se); //SE音量調整 255最大音量から80%再生
			PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE); //SE再生
			credit = false;
		}
	}

	else
	{

		//入力受付るのか
		if (++input_time > INPUT_ACCEPTANCE_TIME)
		{
			if (key->GetStickAngle(L).y > 0)
			{

				ChangeVolumeSoundMem(255 * 40 / 100, move_se); //SE音量調整 255最大音量から80%再生
				PlaySoundMem(move_se, DX_PLAYTYPE_BACK, TRUE); //SE再生

				if (++select_menu == MENU_NUM)select_menu = 0;
				input_time = 1;
			}
			else if (key->GetStickAngle(L).y < 0)
			{

				ChangeVolumeSoundMem(255 * 40 / 100, move_se); //SE音量調整 255最大音量から80%再生
				PlaySoundMem(move_se, DX_PLAYTYPE_BACK, TRUE); //SE再生

				if (--select_menu < 0)select_menu = MENU_NUM - 1;
				input_time = 1;
			}
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

		DrawRotaGraph(990, 250 + (i * 100), 1, 0, menu_image[i][flg], TRUE);
	}

	if (help)
	{
		DrawRotaGraph(640, 400, 1.15f, 0, help_image[help_menu], TRUE);
		DrawRotaGraph(1000, 100, 1, 0, num_image[help_menu + 1], TRUE);
		DrawRotaGraph(1040, 100, 1, 0, slash_image[1], TRUE);
		DrawRotaGraph(1080, 100, 1, 0, num_image[3], TRUE);
	}

	if (credit)
	{
		DrawRotaGraph(640, 400, 1.15f, 0, credit_image, TRUE);
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
			StopSoundMem(bgm);
			return new StageSelect(0);
			break;

		case 3: //ゲーム終了
			return nullptr;
			break;
		}
	}

	if (help == false && credit == false)
	{
		//操作しなかったら紙芝居
		if (input_time % 600 == 0)
		{
			StopSoundMem(bgm);
			return new Opening();
		}
	}


	return this;
}