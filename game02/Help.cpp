#include "Help.h"
#include"Title.h"
#include"DxLib.h"


Help::Help()
{
	image = LoadGraph("images/helpimage2.png");
	chane_title = false;
	flashing_time = 0;
}

void Help::Update(Key* key)
{
	if (key->KeyDown(B))
	{
		chane_title = true;
	}

	if (++flashing_time >= 60)
	{
		flashing_time = 0;
	}
}

void Help::Draw() const
{
	DrawGraph(0, 0, image, false);

	if (flashing_time / 30 == 0)
	{
		DrawString(1000, 600, "Bƒ{ƒ^ƒ“", GetColor(0, 0, 0));
	}

}

AbstractScene* Help::ChangeScene()
{

	if (chane_title)
	{
		return new Title();
	}
	else
	{
		return this;
	}

}