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
	back_ground_image = LoadGraph("images/StageSelect/stageselect1.png");
	LoadDivGraph("images/StageSelect/number.png", 10, 10, 1, 35, 38, number_image);
	LoadDivGraph("images/player.png", 4, 4, 1, 30, 30, player_image);
	stage_number = stage_num;
	operating_time = 0;
	transition = false;
	cursor_x = 0;
	cursor_y = 0;
	player_x = 0;
	player_y = 0;

	FILE* fp_s;//スコアファイル読み込み
	FILE* fp_w;//スコアファイル読み込み
	fopen_s(&fp_s, "data/hiscore.txt", "r");
	fopen_s(&fp_w, "data/stagewidth.txt", "r");
	for (int i = 0; i < STAGE_NUM; i++)
	{
		fscanf_s(fp_s, "%d", &stage_score[i]);
		fscanf_s(fp_w, "%d", &stage_width[i]);
	}
	fclose(fp_s);
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
	//スティックを動かしたら
	if (key->GetStickAngle(L).x == 0)operating_time = TIME;
	else operating_time++;

	//操作受け
	if (operating_time >= TIME)
	{
		if (key->GetStickAngle(L).x > 0)
		{
			if (++stage_number > 2)stage_number = 0;
			operating_time = 0;
		}
		else if(key->GetStickAngle(L).x < 0)
		{
			if (--stage_number < 0)stage_number = 2;
			operating_time = 0;
		}
	}

	if (key->KeyDown(B))transition = TRUE;

	if (key->KeyPressed(RIGHT))
	{
		++player_x;
	}
	if (key->KeyPressed(LEFT))
	{
		--player_x;
	}
	if (key->KeyPressed(UP))
	{
		--player_y;
	}
	if (key->KeyPressed(DOWN))
	{
		++player_y;
	}
}

//-----------------------------------
// 描画
//-----------------------------------
void StageSelect::Draw() const
{
	DrawRotaGraph(640, 360, 1, 0, back_ground_image, TRUE);

	int score_keta = 1000000;
	int stage_keta = 10;
	int cnt = 0;
	int score = stage_score[stage_number];
	int stage_number = this->stage_number + 1;

	DrawRotaGraph(player_x, player_y, 1, 0, player_image[0], TRUE, direction);
	DrawFormatString(200, 400, 0xffffff, "%f", player_x);
	DrawFormatString(200, 500, 0xffffff, "%f", player_y); 

	while (score_keta > 0)
	{
		//スコア表示
		int image_type = (score / score_keta);
		DrawRotaGraph(680 + (cnt * 50), 630, 1, 0, number_image[image_type], TRUE);
		score -= (image_type * score_keta);
		score_keta = (score_keta / 10);
		//ステージ数表示
		if (stage_keta > 0)
		{
			image_type = (stage_number / stage_keta);
			DrawRotaGraph(450 + (cnt * 50), 160, 1, 0, number_image[image_type], TRUE);
			stage_number -= (image_type * stage_keta);
			stage_keta = (stage_keta / 10);
		}
		cnt++;
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
		return new GameMain(stage_number, stage_width[stage_number]);
	}

	return this;
}
