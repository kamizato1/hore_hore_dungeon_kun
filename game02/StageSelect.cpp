#include"DxLib.h"
#include "StageSelect.h"
#include "GameMain.h"

//操作受付時間
#define TIME 30

//スティックの感度
#define SENSITIVITY 1000

//-----------------------------------
// コンストラクタ
//-----------------------------------
StageSelect::StageSelect(int stage_num)
{
	back_ground_image = LoadGraph("images/StageSelect/map.png");
	LoadDivGraph("images/StageSelect/number.png", 10, 10, 1, 35, 38, number_image);
	LoadDivGraph("images/Player/player1.png", 5, 5, 1, 30, 30, player_image);
	stage_number = stage_num;
	operating_time = TIME / 2;
	player_image_change_time = TIME;
	transition = false;
	player_image_type = 0;
	
	FILE* fp_s;//スコアファイル読み込み
	fopen_s(&fp_s, "data/hiscore.txt", "r");
	for (int i = 0; i < STAGE_NUM; i++)fscanf_s(fp_s, "%d", &stage_score[i]);
	fclose(fp_s);

	player_location[0].x = 490;
	player_location[0].y = 520;
	player_location[1].x = 670;
	player_location[1].y = 520;
	player_location[2].x = 710;
	player_location[2].y = 360;
	player_location[3].x = 940;
	player_location[3].y = 390;
	player_location[4].x = 900;
	player_location[4].y = 220;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
StageSelect::~StageSelect()
{

}

//-----------------------------------
// 更新
//-----------------------------------
void StageSelect::Update(Key* key)
{
	if (--player_image_change_time <= 0)
	{
		player_image_change_time = TIME / 2;
		if (++player_image_type > 3)player_image_type = 0;
	}

	//スティックを動かしたら
	if (key->GetStickAngle(L).x == 0)operating_time = 0;
	else operating_time--;

	//操作受け
	if (operating_time < 0)
	{
		if (key->GetStickAngle(L).x > 0)
		{
			if (++stage_number >= STAGE_NUM)stage_number = 0;
			operating_time = TIME;
		}
		else if (key->GetStickAngle(L).x < 0)
		{
			if (--stage_number < 0)stage_number = STAGE_NUM - 1;
			operating_time = TIME;
		}
	}

	if (key->KeyDown(B))transition = TRUE;
	}

	//-----------------------------------
	// 描画
	//-----------------------------------
	void StageSelect::Draw() const
	{
		DrawRotaGraph(640, 360, 1, 0, back_ground_image, TRUE);

		int score_digit = 1000000;
		int stage_digit = 10;
		int count = 0;
		int stage_score = this->stage_score[stage_number];
		int stage_number = this->stage_number + 1;

		DrawRotaGraph(player_location[this->stage_number].x, player_location[this->stage_number].y, 1, 0, player_image[player_image_type], TRUE);
		
		while (score_digit > 0)
		{
			//スコア表示
			int image_type = (stage_score / score_digit);
			DrawRotaGraph(650 + (count * 50), 630, 1, 0, number_image[image_type], TRUE);
			stage_score -= (image_type * score_digit);
			score_digit = (score_digit / 10);
			//ステージ数表示
			if (stage_digit > 0)
			{
				image_type = (stage_number / stage_digit);
				DrawRotaGraph(450 + (count * 50), 160, 1, 0, number_image[image_type], TRUE);
				stage_number -= (image_type * stage_digit);
				stage_digit = (stage_digit / 10);
			}
			count++;
		}
	}

	//-----------------------------------
	// 遷移
	//-----------------------------------
	AbstractScene* StageSelect::ChangeScene()
	{
		//次の画面に遷移するのか
		if (transition)
		{
			return new GameMain(stage_number);
		}

		return this;
	}
