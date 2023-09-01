#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"GameOver.h"
#include"Key.h"

#define FONT_SPEED 3

GameOver::GameOver()
{
	back_ground_image = LoadGraph("images/gameoverimage.png");
	LoadDivGraph("images/gameover1.png", 8, 8, 1, 110, 110, font_image);
	for (int i = 0; i < FONT_NUM; i++)
	{
		font_location[i].y = -100 + -GetRand(100);
		if(i <= 3)font_location[i].x = 320 + (i * 85);
		else font_location[i].x = 370 + (i * 85);
	}
}

void GameOver::Update(Key* key)
{
	for (int i = 0; i < FONT_NUM; i++)
	{
		if ((font_location[i].y += FONT_SPEED) > 220)
		{
			font_location[i].y = 220;
		}
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
    return this;
}