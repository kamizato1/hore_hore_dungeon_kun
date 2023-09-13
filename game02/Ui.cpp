#include"DxLib.h"

#include"Ui.h"

#define WAIT_TIME 180

Ui::Ui()
{
	LoadDivGraph("images/Ui/item.png", 3, 3, 1, 100, 100, item_image);
	LoadDivGraph("images/Ui/sign.png", 2, 2, 1, 20, 40, sign_image);
	LoadDivGraph("images/Ui/treasure.png", TREASURE_TYPE_NUM, TREASURE_TYPE_NUM, 1, 40, 40, treasure_image);
	clear_image = LoadGraph("images/Ui/clear.png");
	timer_image = LoadGraph("images/Ui/timer.png");
	life_image = LoadGraph("images/Ui/player.png");
	LoadDivGraph("images/Ui/block.png", 2, 2, 1, 160, 160, block_image);
	LoadDivGraph("images/Ui/number.png", 10, 10, 1, 20, 40, number_image);
	wait_time = WAIT_TIME;
	end_clear_walk = FALSE;
	clear_image_size = 0.0f;
}

bool Ui::Update(bool clear)
{
	if (clear)
	{
		if (!end_clear_walk)
		{
			if (--wait_time <= 0)
			{
				wait_time = WAIT_TIME;
				end_clear_walk = TRUE;
			}
		}
		else return MoveClearImage();
	}
	return FALSE;
}

bool Ui::MoveClearImage()
{
	clear_image_size += 0.1f;
	if (clear_image_size > 1.0f)
	{
		clear_image_size = 1.0f;
		if (--wait_time <= 0)return TRUE;
	}
	return FALSE;
}

void Ui::Draw(int time, int life, PLAYER_UI player_ui) const
{
	for (int i = 0; i < TREASURE_TYPE_NUM; i++)DrawRotaGraph(30, 150 + (i * 50), 1, 0, treasure_image[i], TRUE);

	DrawRotaGraph(30, 30, 1, 0, timer_image, TRUE);

	DrawRotaGraph(30, 80, 1, 0, life_image, TRUE);
	DrawRotaGraph(65, 80, 0.9, 0, number_image[0], TRUE);
	DrawRotaGraph(80, 80, 0.9, 0, number_image[life], TRUE);
	

	int timer_digit = 100;
	int treasure_num_digit = 10;
	int count = 0;

	while (timer_digit > 0)
	{
		int image_type = (time / timer_digit);
		DrawRotaGraph(65 + (count * 15), 30, 0.9, 0, number_image[image_type], TRUE);
		time -= (image_type * timer_digit);
		timer_digit = (timer_digit / 10);

		if (treasure_num_digit > 0)
		{
			for (int i = 0; i < TREASURE_TYPE_NUM; i++)
			{
				image_type = (player_ui.treasure_num[i] / treasure_num_digit);
				DrawRotaGraph(65 + (count * 15), 150 + (i * 50), 0.9, 0, number_image[image_type], TRUE);
				player_ui.treasure_num[i] -= (image_type * treasure_num_digit);
			}
			treasure_num_digit = (treasure_num_digit / 10);
		}

		count++;
	}
	int block_set_time = ((BLOCK_SET_TIME - player_ui.block_set_time) / 3);

	DrawRotaGraph(640, 55, 1, 0, item_image[player_ui.item_type], TRUE);
	if (player_ui.item_type == 1)DrawCircleGauge(640, 55, block_set_time, block_image[0]);

	int item = player_ui.item_type - 1;
	if (item < 0)item = 2;
	DrawRotaGraph(560, 35, 0.5, 0, item_image[item], TRUE);
	if (item == 1)DrawCircleGauge(560, 35, block_set_time, block_image[1]);

	item = player_ui.item_type + 1;
	if (item > 2)item = 0;
	DrawRotaGraph(720, 35, 0.5, 0, item_image[item], TRUE);
	if (item == 1)DrawCircleGauge(720, 35, block_set_time, block_image[1]);

	DrawRotaGraph(640, 300, clear_image_size, 0, clear_image, TRUE);
	
}