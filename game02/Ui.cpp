#include"DxLib.h"

#include"Ui.h"

#define WAIT_TIME 180

Ui::Ui()
{
	LoadDivGraph("images/Ui/item.png", ITEM_TYPE_NUM, ITEM_TYPE_NUM, 1, 100, 100, item_image);
	LoadDivGraph("images/Ui/treasure.png", TREASURE_TYPE_NUM, TREASURE_TYPE_NUM, 1, 40, 40, treasure_image);
	clear_image = LoadGraph("images/Ui/clear.png");
	timer_image = LoadGraph("images/Ui/timer.png");
	life_image = LoadGraph("images/Ui/player.png");
	cross_image = LoadGraph("images/Ui/cross.png");

	int count = 0;
	LoadDivGraph("images/Ui/darkitem.png", 6, 2, ITEM_TYPE_NUM, 160, 160, set_dark_item_image);
	for (int i = 0; i < ITEM_TYPE_NUM; i++)
	{
		for (int j = 0; j < 2; j++)this->dark_item_image[i][j] = set_dark_item_image[count++];
	}
	LoadDivGraph("images/Ui/number.png", 10, 10, 1, 20, 40, number_image);

	wait_time = WAIT_TIME;
	end_clear_walk = FALSE;
	clear_image_size = 0.0f;
}

void Ui::Delete()
{
	DeleteGraph(clear_image);
	DeleteGraph(life_image);
	DeleteGraph(timer_image);
	DeleteGraph(cross_image);

	for (int i = 0; i < 10; i++)DeleteGraph(number_image[i]);

	for (int i = 0; i < ITEM_TYPE_NUM; i++)DeleteGraph(item_image[i]);

	for (int i = 0; i < 6; i++)DeleteGraph(set_dark_item_image[i]);

	for (int i = 0; i < TREASURE_TYPE_NUM; i++)DeleteGraph(treasure_image[i]);

	for (int i = 0; i < ITEM_TYPE_NUM; i++)
	{
		for (int j = 0; j < 2; j++)DeleteGraph(dark_item_image[i][j]);
	}

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

void Ui::Draw(int time, int life, int pickaxe_flg, PLAYER_UI player_ui) const
{
	for (int i = 0; i < TREASURE_TYPE_NUM; i++)DrawRotaGraph(30, 150 + (i * 50), 1, 0, treasure_image[i], TRUE);

	DrawRotaGraph(30, 30, 1, 0, timer_image, TRUE);

	DrawRotaGraph(30, 80, 1, 0, life_image, TRUE);
	DrawRotaGraph(65, 80, 0.9, 0, number_image[0], TRUE);
	DrawRotaGraph(80, 80, 0.9, 0, number_image[life], TRUE);


	int timer_digit = 100;
	int treasure_num_digit = 10;
	int count = 0;

	player_ui.break_block_num = 50 - player_ui.break_block_num;

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
			
			image_type = (player_ui.break_block_num / treasure_num_digit);
			DrawRotaGraph(23 + (count * 12), 150, 0.7, 0, number_image[image_type], TRUE);
			player_ui.break_block_num -= (image_type * treasure_num_digit);

			treasure_num_digit = (treasure_num_digit / 10);
		}
		count++;
	}

	for (int i = 0; i < ITEM_TYPE_NUM; i++)player_ui.now_item_set_time[i] = (player_ui.now_item_set_time[i] / player_ui.item_set_time[i]) * 100;
	DrawRotaGraph(640, 55, 1, 0, item_image[player_ui.item_type], TRUE);
	if (player_ui.item_type == 0)
	{
		if (pickaxe_flg)DrawRotaGraph(640, 55, 1, 0, dark_item_image[player_ui.item_type][0], TRUE);
		else DrawRotaGraph(640, 55, 1, 0, cross_image, TRUE);
	}
	else
	{
		DrawCircleGauge(640, 55, player_ui.now_item_set_time[player_ui.item_type], dark_item_image[player_ui.item_type][0]);
		if(player_ui.now_item_set_time[player_ui.item_type] < 100)DrawRotaGraph(640, 55, 1, 0, cross_image, TRUE);
	}

	int item_type = player_ui.item_type - 1;
	if (item_type < 0)item_type = 2;
	DrawRotaGraph(560, 35, 0.5, 0, item_image[item_type], TRUE);
	if (item_type == 0)
	{
		if (pickaxe_flg)DrawRotaGraph(560, 35, 1, 0, dark_item_image[item_type][1], TRUE);
	}
	else DrawCircleGauge(560, 35, player_ui.now_item_set_time[item_type], dark_item_image[item_type][1]);

	item_type = player_ui.item_type + 1;
	if (item_type > 2)item_type = 0;
	DrawRotaGraph(720, 35, 0.5, 0, item_image[item_type], TRUE);
	if (item_type == 0)
	{
		if (pickaxe_flg)DrawRotaGraph(720, 35, 1, 0, dark_item_image[item_type][1], TRUE);
	}
	else DrawCircleGauge(720, 35, player_ui.now_item_set_time[item_type], dark_item_image[item_type][1]);

	DrawRotaGraph(640, 300, clear_image_size, 0, clear_image, TRUE);
}