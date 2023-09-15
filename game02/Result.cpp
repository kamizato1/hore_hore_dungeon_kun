#include "Result.h"
#include"DxLib.h"
#include"StageSelect.h"

#define WAIT_TIME 90

//-----------------------------------
// コンストラクタ
//-----------------------------------
Result::Result(int stage_num, int* treasure_num)
{
	
	decision_se = LoadSoundMem("bgm/click.mp3");
	roll_score_se = LoadSoundMem("bgm/PickaxeThrow.mp3");
	set_score_se = LoadSoundMem("bgm/ExplosionSE.mp3");
	result_bgm = LoadSoundMem("bgm/Result.mp3");
	drum_roll_se = LoadSoundMem("bgm/DrumRoll.mp3");
	drum_se = LoadSoundMem("bgm/drum.mp3");
	stamp_se = LoadSoundMem("bgm/stamp.mp3");

	stamp_image = LoadGraph("images/Result/stamp.png");
	map_image = LoadGraph("images/Result/map.png");
	score_image = LoadGraph("images/Result/score.png");
	back_ground_image[0] = LoadGraph("images/background03.png");
	back_ground_image[1] = LoadGraph("images/background02.png");
	back_ground_image[2] = LoadGraph("images/background01.png");
	LoadDivGraph("images/Result/number.png", 10, 10, 1, 140, 150, number_image);
	LoadDivGraph("images/Result/treasure.png", TREASURE_TYPE_NUM, TREASURE_TYPE_NUM, 1, 60, 60, treasure_image);
	LoadDivGraph("images/Result/sign.png", 3, 3, 1, 150, 150, sign_image);

	score_image_size = 15.0f;
	score_image_angle = 0.0f;
	for (int i = 0; i < 3; i++)back_ground_image_x[i] = 0.0f;

	stamp_image_size = 3.0f;

	transition = FALSE;
	end_move_score = FALSE;
	end_add_score = FALSE;
	end_move_stamp = FALSE;
	stamp_flg = FALSE;
	new_record = FALSE;
	skip = FALSE;

	PlaySoundMem(roll_score_se, DX_PLAYTYPE_LOOP, TRUE);

	treasure_price[0] = 50000;
	treasure_price[1] = 150000;
	treasure_price[2] = 500000;
	treasure_price[3] = 1000000;
	treasure_price[4] = 2000000;

	for (int i = 0; i < TREASURE_TYPE_NUM; i++)this->treasure_num[i] = treasure_num[i];
	this->stage_num = stage_num;
	wait_time = WAIT_TIME;

	score = 0;

	for (int i = 0; i < TREASURE_TYPE_NUM; i++)
	{
		treasure_score[i] = treasure_num[i] * treasure_price[i];
		score += treasure_score[i];
		if (treasure_score[i] > 9999999)treasure_score[i] = 9999999;

		treasure_add_score[i] = treasure_score[i] / 299;
		if (treasure_score[i] < 299) treasure_add_score[i] = 1;
	}
	
	if (score > 9999999)score = 9999999;
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
		for (int i = 0; i < STAGE_NUM; i++)fprintf(fp_s, "%d\n", hi_score[i]);
		fclose(fp_s);
	}
	score = 0;

	int stage = stage_num + 2;
	int clear_stage;

	FILE* fp_c; //クリア済みのステージ
	fopen_s(&fp_c, "data/clearstage.txt", "r");
	fscanf_s(fp_c, "%d", &clear_stage);
	fclose(fp_c);

	if (clear_stage != 5)
	{
		//ステージ解放
		if (stage > clear_stage)
		{
			fopen_s(&fp_c, "data/clearstage.txt", "w");
			fprintf(fp_c, "%d\n", stage);
			fclose(fp_c);
		}
	}
}

void Result::Delete()
{
	DeleteSoundMem(decision_se);
	DeleteSoundMem(roll_score_se);
	DeleteSoundMem(set_score_se);
	DeleteSoundMem(result_bgm);
	DeleteSoundMem(drum_roll_se);
	DeleteSoundMem(drum_se);
	DeleteSoundMem(stamp_se);
	

	DeleteGraph(stamp_image);
	DeleteGraph(map_image);
	DeleteGraph(score_image);
	
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(treasure_image[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(number_image[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(sign_image[i]);
		DeleteGraph(back_ground_image[i]);
	}

}

//-----------------------------------
// 更新
//-----------------------------------
void Result::Update(Key* key)
{
	if (key->KeyDown(B))
	{
		if (end_move_stamp)
		{
			PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE);
			transition = TRUE;
		}
		else if(end_move_score)skip = TRUE;

		StopSoundMem(drum_roll_se);
	}

	if (!end_move_score)MoveScore();
	else if (!end_add_score)AddScore();
	else if (!end_move_stamp)MoveStamp();

	if ((back_ground_image_x[0] -= 0.3f) < -SCREEN_WIDTH)back_ground_image_x[0] = 0.0f;
	if ((back_ground_image_x[1] -= 0.5f) < -SCREEN_WIDTH)back_ground_image_x[1] = 0.0f;
	if (--back_ground_image_x[2] < -SCREEN_WIDTH)back_ground_image_x[2] = 0.0f;
}

void Result::MoveScore()
{
	if (score_image_size > 0.8f)
	{
		score_image_size -= 0.2f;
		score_image_angle += 0.4f;

		if (score_image_size <= 0.8f)
		{
			StopSoundMem(roll_score_se);
			PlaySoundMem(set_score_se, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else
	{
		score_image_size = 0.8f;
		score_image_angle = 0.0f;
		if (--wait_time <= 0)
		{
			end_move_score = TRUE;
			wait_time = WAIT_TIME;
			PlaySoundMem(result_bgm, DX_PLAYTYPE_LOOP, TRUE);
			PlaySoundMem(drum_roll_se, DX_PLAYTYPE_LOOP, TRUE);
		}
	}
}

void Result::AddScore()
{
	end_add_score = TRUE;
	if (!skip)
	{
		for (int i = 0; i < TREASURE_TYPE_NUM; i++)
		{
			int add_score = treasure_score[i];
			if (add_score >= treasure_add_score[i])add_score = treasure_add_score[i];
			treasure_score[i] -= add_score;
			score += add_score;
			if (treasure_score[i] != 0)end_add_score = FALSE;
		}
		if (end_add_score)
		{
			if (wait_time == WAIT_TIME)
			{
				PlaySoundMem(drum_se, DX_PLAYTYPE_BACK, TRUE);
				StopSoundMem(drum_roll_se);
			}
			if (--wait_time <= 0)wait_time = WAIT_TIME;
			else end_add_score = FALSE;
		}
	}
	else
	{
		for (int i = 0; i < TREASURE_TYPE_NUM; i++)
		{
			int add_score = treasure_score[i];
			treasure_score[i] -= add_score;
			score += add_score;
			wait_time = WAIT_TIME;
		}
	}

	if (score > 9999999)score = 9999999;
}

void Result::MoveStamp()
{
	if (new_record)
	{
		stamp_flg = TRUE;
		if (stamp_image_size > 1.0f)stamp_image_size -= 0.15f;
		else
		{
			stamp_image_size = 1.0f;
			if (wait_time == WAIT_TIME)PlaySoundMem(stamp_se, DX_PLAYTYPE_BACK, TRUE);
			if (--wait_time <= 0)wait_time = WAIT_TIME, end_move_stamp = TRUE;
		}


	}
	else
	{
		if ((wait_time == WAIT_TIME) && (skip))PlaySoundMem(drum_se, DX_PLAYTYPE_BACK, TRUE);

		if (--wait_time <= 0)
		{
			wait_time = WAIT_TIME;
			end_move_stamp = TRUE;
		}
	}
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
	DrawRotaGraph(640, 360, 1, 0, map_image, TRUE);

	int count = 0;
	int score_digit = 1000000;
	int score = this->score;

	while (score_digit > 0)
	{
		int image_type = (score / score_digit);
		DrawRotaGraph(430 + (count * 70), 230, 0.4, 0, number_image[image_type], TRUE);
		score -= (image_type * score_digit);
		score_digit = (score_digit / 10);
		count++;
	}

	for (int i = 0; i < TREASURE_TYPE_NUM; i++)
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

	DrawRotaGraph(640, 120, score_image_size, score_image_angle, score_image, TRUE);
	if (stamp_flg)DrawRotaGraph(640, 480, stamp_image_size, 0.2, stamp_image, TRUE);
}

//-----------------------------------
// 遷移
//-----------------------------------
AbstractScene* Result::ChangeScene()
{
	if (transition)
	{
		StopSoundMem(result_bgm);
		return new StageSelect(stage_num);
	}
	return this;
}
