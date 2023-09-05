#include "Result.h"
#include"DxLib.h"

#define WAIT_TIME 120

//-----------------------------------
// コンストラクタ
//-----------------------------------
Result::Result(int stage_num, int* treasure_num)
{
	stamp_image = LoadGraph("images/Result/stamp.png");
	map_image = LoadGraph("images/Result/scoremap.png");
	score_image = LoadGraph("images/Result/score.png");
	back_ground_image[0] = LoadGraph("images/background03.png");
	back_ground_image[1] = LoadGraph("images/background02.png");
	back_ground_image[2] = LoadGraph("images/background01.png");
	LoadDivGraph("images/Result/number.png", 10, 10, 1, 140, 151, number_image);
	LoadDivGraph("images/Result/treasure.png", 4, 4, 1, 60, 60, treasure_image);
	LoadDivGraph("images/Result/sign.png", 3, 3, 1, 150, 150, sign_image);

	score_image_size = 15;
	score_image_angle = 0;
	for (int i = 0; i < 3; i++)back_ground_image_x[i] = 0;

	stamp_image_size = 3;

	transition = FALSE;
	end_move_score = FALSE;
	end_add_score = FALSE;
	end_move_stamp = FALSE;
	stamp_flg = FALSE;
	new_record = FALSE;
	skip = FALSE;

	treasure_price[0] = 50000;
	treasure_price[1] = 150000;
	treasure_price[2] = 500000;
	treasure_price[3] = 1000000;

	for (int i = 0; i < TREASURE_NUM; i++)this->treasure_num[i] = treasure_num[i];
	
	wait_time = WAIT_TIME;

	score = 0;

	for (int i = 0; i < TREASURE_NUM; i++)
	{
		treasure_score[i] = this->treasure_num[i] * treasure_price[i];
		score += treasure_score[i];
	}

	int hi_score[STAGE_NUM];
	FILE* fp_s;//ステージ１ファイル読み込み
	fopen_s(&fp_s, "data/hiscore.txt", "r");
	for (int i = 0; i < STAGE_NUM; i++)fscanf_s(fp_s, "%d", &hi_score[i]);
	fclose(fp_s);

	if (score > hi_score[stage_num])
	{
		new_record = TRUE;
		hi_score[stage_num] = score;
		fopen_s(&fp_s, "data/hiscore.txt", "w");
		for (int i = 0; i < STAGE_NUM; i++)fprintf(fp_s, "%d ", hi_score[i]);
		fclose(fp_s);
	}
	score = 0;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Result::~Result()
{

}

//-----------------------------------
// 更新
//-----------------------------------
void Result::Update(Key* key)
{
	if (key->KeyDown(B))
	{
		if (wait_time <= 0)transition = TRUE;
		else skip = TRUE;
	}

	if (!end_move_score)MoveScore();
	else if (!end_add_score)AddScore();
	else if (!end_move_stamp)MoveStamp();
	else wait_time--;

	if ((back_ground_image_x[0] -= 0.3) < -SCREEN_WIDTH)back_ground_image_x[0] = 0;
	if ((back_ground_image_x[1] -= 0.5) < -SCREEN_WIDTH)back_ground_image_x[1] = 0;
	if (--back_ground_image_x[2] < -SCREEN_WIDTH)back_ground_image_x[2] = 0;
}

void Result::MoveScore()
{
	if ((score_image_size > 0.8) && (!skip))
	{
		score_image_size -= 0.2;
		score_image_angle += 0.4;
	}
	else
	{
		score_image_size = 0.8;
		score_image_angle = 0;
		end_move_score = TRUE;
	}
}

void Result::AddScore()
{
	end_add_score = TRUE;
	for (int i = 0; i < TREASURE_NUM; i++)
	{
		int add_score = treasure_score[i];
		if ((add_score >= 10000) && (!skip))add_score = 10000;
		treasure_score[i] -= add_score;
		score += add_score;
		if (treasure_score[i] != 0)end_add_score = FALSE;
	}
}

void Result::MoveStamp()
{
	if (new_record)
	{
		stamp_flg = TRUE;
		if ((stamp_image_size > 1) && (!skip))stamp_image_size -= 0.15;
		else stamp_image_size = 1, end_move_stamp = TRUE;
	}
	else end_move_stamp = TRUE;
}


//-----------------------------------
// 描画
//-----------------------------------
void Result::Draw() const
{
	for (int i = 0; i < 3; i++)
	{
		DrawGraph(back_ground_image_x[i], 0, back_ground_image[i], TRUE);
		DrawGraph(back_ground_image_x[i] + SCREEN_WIDTH, 0, back_ground_image[i], TRUE);
	}
	DrawRotaGraph(640, 360, 1,0,map_image, TRUE);

	int count = 0;
	int score_digit = 1000000;
	int score = this->score;

	while (score_digit > 0)
	{
		int image_type = (score / score_digit);
		DrawRotaGraph(430 + (count * 70), 250, 0.4, 0, number_image[image_type], TRUE);
		score -= (image_type * score_digit);
		score_digit = (score_digit / 10);
		count++;
	}

	for (int i = 0; i < TREASURE_NUM; i++)
	{
		DrawRotaGraph(300, 340 + (60 * i), 0.7, 0, treasure_image[i], TRUE);
		DrawRotaGraph(430, 340 + (60 * i), 0.3, 0, sign_image[0], TRUE);
		DrawRotaGraph(740, 340 + (60 * i), 0.3, 0, sign_image[1], TRUE);

		count = 0;
		score_digit = 1000000;
		score = treasure_score[i];
		int treasure_price = this->treasure_price[i];
		int num_digit = 10;
		int treasure_num = this->treasure_num[i];
		
		while (score_digit > 0)
		{
			int image_type = (score / score_digit);
			DrawRotaGraph(800 + (35 * count), 340 + (60 * i), 0.2, 0, number_image[image_type], TRUE);
			score -= (image_type * score_digit);

			image_type = (treasure_price / score_digit);
			DrawRotaGraph(480 + (35 * count), 340 + (60 * i), 0.2, 0, number_image[image_type], TRUE);
			treasure_price -= (image_type * score_digit);

			score_digit = (score_digit / 10);

			if (num_digit > 0)
			{
				image_type = (treasure_num / num_digit);
				DrawRotaGraph(350 + (35 * count), 340 + (60 * i), 0.2, 0, number_image[image_type], TRUE);
				treasure_num -= (image_type * num_digit);
				num_digit = (num_digit / 10);
			}
			count++;
		}
	}

	DrawRotaGraph(640, 140, score_image_size, score_image_angle, score_image, TRUE);
	if (stamp_flg)DrawRotaGraph(640, 460, stamp_image_size, 0.2, stamp_image, TRUE);
}

//-----------------------------------
// 遷移
//-----------------------------------
AbstractScene* Result::ChangeScene()
{
	if (transition)return nullptr;
	return this;
}
