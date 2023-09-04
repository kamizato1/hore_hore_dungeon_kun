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

	animation_image[0]= LoadGraph("images/Opening/���ŋ�5�@�L�����̂�.png");
	animation_image[1] = LoadGraph("images/Opening/���ŋ�5�@�L�����e�̂�.png");
	animation_image[2] = LoadGraph("images/Opening/���ŋ�5�@��.png");
	animation_image[3] = LoadGraph("images/Opening/���ŋ�5�@��.png");
	animation_image[4] = LoadGraph("images/Opening/���ŋ�5�@��.png");
	animation_image[5] = LoadGraph("images/Opening/���ŋ�5�@���H�̂�.png");
	animation_image[6] = LoadGraph("images/Opening/���ŋ�5�@�؁X.png");

	animation = 0;
	animation_time = 0;
	display_time = 0;
	time = 0;
	story_no = 0;

	can_scene_change = false;

}

Opening::~Opening()
{

}

void Opening::Update(Key* key)
{
	//START�L�[�������ꂽ�A�������͎��ŋ��I�����Ƀ^�C�g����
	if (key->KeyDown(START) || story_no > 5)
	{
		can_scene_change = true;
	}

	if (key->KeyDown(B))
	{
		++story_no;
	}

	/*if (key->KeyDown(A))
	{
		display_time =display_time+10;
	}*/

	////�o�ߎ��ԑ���
	/*if (time % 60 == 0)
	{
		++display_time;
	}*/


	//60�Ł��ƕb�Ɏ���
	if (++time % 300 == 0) 
	{
		++story_no;
	}



}

void Opening::Draw() const
{
	if (story_no < 4)
	{
		DrawGraph(0, 0, image[story_no], false);
	}
	else
	{
		DrawRotaGraph(640, 360, 1,0, image[4], TRUE);
	}

	/*DrawRotaGraph(640, 360, 1, 0, animation_image[3], false);

	DrawRotaGraph(640, 360, 1, 0, animation_image[5], true);

	DrawRotaGraph(640, 360, 1, 0, animation_image[2], true);

	DrawRotaGraph(640, 360, 1, 0, animation_image[6], true);

	DrawRotaGraph(640, 360, 1, 0, animation_image[4], true);

	DrawRotaGraph(640, 360, 1, 0, animation_image[1], true);

	DrawRotaGraph(640, 360, 1, 0, animation_image[0], true);



	DrawFormatString(200, 400, 0xffffff, "%d", story_no);*/

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
