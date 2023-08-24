#include"DxLib.h"
#include"Ui.h"

Ui::Ui()
{
	life_image = LoadGraph("images/life.png");
	LoadDivGraph("images/number02.png", 10, 10, 1, 20, 40, number_image);
}

void Ui::Update()
{
}

void Ui::Draw(int time, int life) const
{
	DrawRotaGraph(45, 30, 1,0,life_image, TRUE);
	DrawRotaGraph(90, 40, 1, 0, number_image[life], TRUE);

	int keta = 100;
	int cnt = 0;
	
	while (keta > 0)
	{
		int image_type = (time / keta);
		DrawRotaGraph(1000 + (cnt * 16), 40, 1, 0, number_image[image_type], TRUE);
		time -= (image_type * keta);
		keta = (keta / 10);
		cnt++;
	}
}