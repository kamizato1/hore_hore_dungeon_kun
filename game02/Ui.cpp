#include"DxLib.h"
#include"Ui.h"

#define WAIT_TIME 180

Ui::Ui()
{
	clear_image = LoadGraph("images/Ui/clear.png");
	life_image = LoadGraph("images/Ui/life.png");
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

void Ui::Draw(int time, int life) const
{
	DrawRotaGraph(45, 30, 1,0,life_image, TRUE);
	DrawRotaGraph(90, 40, 1, 0, number_image[life], TRUE);

	int digit = 100;
	int count = 0;
	
	while (digit > 0)
	{
		int image_type = (time / digit);
		DrawRotaGraph(1000 + (count * 16), 40, 1, 0, number_image[image_type], TRUE);
		time -= (image_type * digit);
		digit = (digit / 10);
		count++;
	}

	DrawRotaGraph(640, 300, clear_image_size, 0, clear_image, TRUE);
}