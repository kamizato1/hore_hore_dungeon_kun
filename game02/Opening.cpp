#include "Opening.h"
#include "DxLib.h"
#include"Title.h"

Opening::Opening()
{
	//���ŋ��摜
	image[0] = LoadGraph("images/Opening/���ŋ�2.png");
	image[1] = LoadGraph("images/Opening/���ŋ�3.png");
	image[2] = LoadGraph("images/Opening/���ŋ�4.png");
	image[3] = LoadGraph("images/Opening/���ŋ�5.png");
	image[4] = LoadGraph("images/Opening/���ŋ�6.png");

	//�����p�摜
	character_image[0] = LoadGraph("images/Opening/Character/�Ƃ���ꌬ�ƁB.png");
	character_image[1] = LoadGraph("images/Opening/Character/���̏��N�͉Ƃ̂����������Ă��܂����B.png");
	character_image[2] = LoadGraph("images/Opening/Character/����Ƃ��Ȃ̒�����Â����������܂����B.png");
	character_image[3] = LoadGraph("images/Opening/Character/�u����́A�g���W���[�n���^�[������.png");
	character_image[4] = LoadGraph("images/Opening/Character/���N�̓^�J�������������ɏo�܂����Ƃ��B.png");


	background_image = LoadGraph("images/Opening/map.png");


	animation = 0;
	animation_time = 0;
	display_time = 0;
	time = 0;
	brightness = 0;
	story_no = 0;

	can_scene_change = false;

}

Opening::~Opening()
{

}

void Opening::Update(Key* key)
{

	int old_story_no = story_no;

	//A�L�[�������ꂽ�A�������͎��ŋ��I�����Ƀ^�C�g����
	if (key->KeyDown(B) || story_no > 4)
	{
		can_scene_change = true;
	}

	//60�Ł��ƕb�Ɏ���
	if (++time % 400 == 0) 
	{
		++story_no;
	}

	if (brightness< 255)
	{
		brightness += 1;
	}


	if (story_no != old_story_no)
	{
		brightness = 0;
	}

}

void Opening::Draw() const
{

	DrawRotaGraph(640, 360, 1, 0, background_image, false);

	SetDrawBright(brightness, brightness, brightness);

	DrawRotaGraph(640, 300,0.7f,0 ,image[story_no], false);

	DrawRotaGraph(640, 630, 0.5, 0, character_image[story_no], true);

	SetDrawBright(225, 225, 225);

}

AbstractScene* Opening::ChangeScene()
{
	//�V�[���؂�ւ�
	if (can_scene_change)
	{
		SetDrawBright(225, 225, 225);
		return new Title();
	}

	return this;
}
