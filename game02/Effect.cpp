#include"DxLib.h"
#include"Effect.h"

#define IMAGE_CHANGE_TIME 2

Effect::Effect(DATA location, int *image)
{
	this->location = location;
	image_change_time = 0;
	can_delete = FALSE;
	image_type = 0;
	for (int i = 0; i < EFFECT_IMAGE_NUM; i++)this->image[i] = image[i];
}

void Effect::Update()
{
	if (++image_change_time > IMAGE_CHANGE_TIME)
	{
		if (++image_type >= EFFECT_IMAGE_NUM)can_delete = TRUE;
		image_change_time = 0;
	}
}

void Effect::Draw(float camera_work)const
{
	DrawRotaGraph(location.x + camera_work, location.y, 1, 0, image[image_type], TRUE, FALSE);
}