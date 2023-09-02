#include "Opening.h"
#include "DxLib.h"
#include"Title.h"

Opening::Opening()
{
	image[0] = LoadGraph("images/Opening/���ŋ�1.png");
	image[1] = LoadGraph("images/Opening/���ŋ�3.png");
	image[2] = LoadGraph("images/Opening/���ŋ�4.png");
	image[3] = LoadGraph("images/Opening/���ŋ�2.png");
	image[4] = LoadGraph("images/Opening/���ŋ�5.png");

	animation = 0;
	animation_time = 0;

	can_scene_change = false;

}

Opening::~Opening()
{

}

void Opening::Update(Key* key)
{
	//START�L�[�������ꂽ�A�������͎��ŋ��I�����Ƀ^�C�g����
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
	//�V�[���؂�ւ�
	if (can_scene_change)
	{
		return new Title();
	}

	return this;
}
