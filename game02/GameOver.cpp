#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"GameOver.h"
#include"Key.h"
#include"StageSelect.h"

#define FONT_SPEED 3
#define WAIT_TIME 300

GameOver::GameOver(int stage_num)
{
	back_ground_image = LoadGraph("images/GameOver/gameoverimage.png");
	LoadDivGraph("images/GameOver/gameover.png", 8, 8, 1, 110, 110, font_image);
	for (int i = 0; i < FONT_NUM; i++)
	{
		font_location[i].y = -100 + -GetRand(100);
		if(i <= 3)font_location[i].x = 320 + (i * 85);
		else font_location[i].x = 370 + (i * 85);
	}
	change_scene = FALSE;
	wait_time = WAIT_TIME;
	this->stage_num = stage_num;
}

void GameOver::Update(Key* key)
{
	for (int i = 0; i < FONT_NUM; i++)
	{
		if ((font_location[i].y += FONT_SPEED) > 220)font_location[i].y = 220;
	}

	if (--wait_time < 0)
	{
		wait_time = 0;
		if (key->KeyDown(B))change_scene = TRUE;
	}
}

void GameOver::Draw()const
{
	DrawGraph(0, 0, back_ground_image, TRUE);
	for (int i = 0; i < FONT_NUM; i++)
	{
		DrawRotaGraph(font_location[i].x, font_location[i].y, 1, 0, font_image[i], TRUE);
	}
}

AbstractScene* GameOver::ChangeScene()
{
	if (change_scene)return new StageSelect(stage_num);
    return this;
}