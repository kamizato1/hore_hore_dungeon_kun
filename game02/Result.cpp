#include "Result.h"
#include"DxLib.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Result::Result(int block_break, int time, int item_block)
{
	map_image = LoadGraph("images/map.png");
	score_image = LoadGraph("images/score.png");
	back_ground_image[0] = LoadGraph("images/background03.png");
	back_ground_image[1] = LoadGraph("images/background02.png");
	back_ground_image[2] = LoadGraph("images/background01.png");
	LoadDivGraph("images/mapnumber.png", 10, 10, 1, 140, 151, number_image);

	score_image_size = 15;
	score_image_angle = 0;
	for (int i = 0; i < 3; i++)move_back_ground_image[i] = 0;

	transition = false;
	end_move_score = false;

	int block = 0;//�A�C�e���i�u���b�N�j

	//�A�C�e���̃u���b�N�̐���0��������u���b�N�̐����P�ɕύX
	if (item_block == 0)block = 1;
	else block = item_block;
	
	//�X�R�A�v�Z
	//�c��u���b�N������
	score = block * time;

	//�󂵂��u���b�N�̐�*(������)
	score = 0;
	//score += 20 * block_break;

//-----------------------------------
// ��̃X�R�A�ɂ��āi�v�l���j
// 
// �J�M 
//-----------------------------------
	
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Result::~Result()
{

}

//-----------------------------------
// �X�V
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
	if (score_image_size > 1)
	{
		score_image_size -= 0.7;
		score_image_angle += 0.5;
	}
	else
	{
		score_image_size = 1;
		score_image_angle = 0;
		end_move_score = TRUE;
	}
}


//-----------------------------------
// �`��
//-----------------------------------
void Result::Draw() const
{
	for (int i = 0; i < 3; i++)
	{
		DrawGraph(move_back_ground_image[i], 0, back_ground_image[i], TRUE);
		DrawGraph(move_back_ground_image[i] + SCREEN_WIDTH, 0, back_ground_image[i], TRUE);
	}

	DrawRotaGraph(640, 360, 1,0,map_image, TRUE);

	int digit = 100000;
	int count = 0;
	int score = this->score;

	while (digit > 0)
	{
		int image_type = (score / digit);
		DrawRotaGraph(470 + (count * 70), 260, 0.4, 0, number_image[image_type], TRUE);
		score -= (image_type * digit);
		digit = (digit / 10);
		count++;
	}

	DrawRotaGraph(640, 150, score_image_size, score_image_angle, score_image, TRUE);

	//�X�R�A���������A���ꂼ��̃X�R�A�̓��_��\��


}

//-----------------------------------
// �J��
//-----------------------------------
AbstractScene* Result::ChangeScene()
{

	if (transition)return nullptr;
	return this;
}
