#include"DxLib.h"
#include"define.h"
#include"Ui.h"

#define WAIT_TIME 180

Ui::Ui()
{
	LoadDivGraph("images/Ui/item.png", 3, 3, 1, 100, 100, item_image);
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

void Ui::Draw(int time, int life, int item_type, int block_set_time) const
{
	DrawRotaGraph(35, 35, 1, 0, timer_image, TRUE);

	int digit = 100, count = 0;
	while (digit > 0)
	{
		int image_type = (time / digit);
		DrawRotaGraph(70 + (count * 17), 32, 1, 0, number_image[image_type], TRUE);
		time -= (image_type * digit);
		digit = (digit / 10);
		count++;
	}

	//DrawRotaGraph(935, 35, 1,0,life_image, TRUE);
	//DrawRotaGraph(75, 40, 1, 0, number_image[0], TRUE);
	//DrawRotaGraph(90, 40, 1, 0, number_image[life], TRUE);

	block_set_time = ((BLOCK_SET_TIME - block_set_time) / 3);

	DrawRotaGraph(640, 55, 1, 0, item_image[item_type], TRUE);
	if (item_type == 1)
	{

		DrawCircleGauge(640, 55, block_set_time, block_image[0]);
	}

	int item = item_type - 1;
	if (item < 0)item = 2;
	DrawRotaGraph(560, 40, 0.5, 0, item_image[item], TRUE);
	if (item == 1)DrawCircleGauge(560, 40, block_set_time, block_image[1]);

	item = item_type + 1;
	if (item > 2)item = 0;
	DrawRotaGraph(720, 40, 0.5, 0, item_image[item], TRUE);
	if (item == 1)DrawCircleGauge(720, 40, block_set_time, block_image[1]);

	DrawRotaGraph(640, 300, clear_image_size, 0, clear_image, TRUE);
	
}