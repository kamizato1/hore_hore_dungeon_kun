#include "Result.h"
#include"DxLib.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
Result::Result(int block_break, int time, int item_block)
{
	map_image = LoadGraph("images/scoremap.png");
	score_image = LoadGraph("images/score1.png");
	back_ground_image[0] = LoadGraph("images/background03.png");
	back_ground_image[1] = LoadGraph("images/background02.png");
	back_ground_image[2] = LoadGraph("images/background01.png");
	LoadDivGraph("images/mapnumber.png", 10, 10, 1, 140, 151, number_image);

	score_image_size = 15;
	score_image_angle = 0;
	for (int i = 0; i < 3; i++)move_back_ground_image[i] = 0;

	transition = false;
	end_move_score = false;

	treasure_num[0] = 18;
	treasure_num[1] = 3;
	treasure_num[2] = 33;
	score = 0000000;
	
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
	if (key->KeyDown(B))transition = true;

	if(!end_move_score)MoveScore();

	if ((move_back_ground_image[0] -= 0.3) < -SCREEN_WIDTH)move_back_ground_image[0] = 0;
	if ((move_back_ground_image[1] -= 0.5) < -SCREEN_WIDTH)move_back_ground_image[1] = 0;
	if (--move_back_ground_image[2] < -SCREEN_WIDTH)move_back_ground_image[2] = 0;
}

void Result::MoveScore()
{
	if (score_image_size > 0.8)
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


//-----------------------------------
// 描画
//-----------------------------------
void Result::Draw() const
{
	for (int i = 0; i < 3; i++)
	{
		DrawGraph(move_back_ground_image[i], 0, back_ground_image[i], TRUE);
		DrawGraph(move_back_ground_image[i] + SCREEN_WIDTH, 0, back_ground_image[i], TRUE);
	}

	DrawRotaGraph(640, 360, 1,0,map_image, TRUE);

	int digit = 1000000;
	int count = 0;
	int score = this->score;

	while (digit > 0)
	{
		int image_type = (score / digit);
		DrawRotaGraph(430 + (count * 70), 250, 0.4, 0, number_image[image_type], TRUE);
		score -= (image_type * digit);
		digit = (digit / 10);
		count++;
	}

	DrawRotaGraph(640, 140, score_image_size, score_image_angle, score_image, TRUE);

	//スコア正式決定後、それぞれのスコアの得点を表示


}

//-----------------------------------
// 遷移
//-----------------------------------
AbstractScene* Result::ChangeScene()
{

	if (transition)return nullptr;
	return this;
}
