#include "Opening.h"
#include "DxLib.h"
#include"Title.h"

Opening::Opening()
{
	image[0] = LoadGraph("images/opening.png");

	animation = 0;
	animation_time = 0;

	can_scene_change = false;

}

Opening::~Opening()
{

}

void Opening::Update(Key* key)
{
	//STARTキーが押された、もしくは紙芝居終了時にタイトルへ
	if (key->KeyDown(START))
	{
		can_scene_change = true;
	}



}

void Opening::Draw() const
{
	DrawGraph(0, 0, image[0], false);
}

AbstractScene* Opening::ChangeScene()
{
	//シーン切り替え
	if (can_scene_change)
	{
		return new Title();
	}

	return this;
}
