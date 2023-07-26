#include"DxLib.h"
#include"BreakBlock.h"

#define IMAGE_CHANGE_TIME 5

BreakBlock::BreakBlock(DATA location)
{
	this->location = location;
	image_change_time = 0;
	LoadDivGraph("images/kakera02.png", 10, 10, 1, 180, 180, image);
	can_delete = FALSE;
	image_type = 0;
}

void BreakBlock::Update()
{
	if (++image_change_time > IMAGE_CHANGE_TIME)
	{
		if (++image_type > IMAGE_TYPE)
		{
			image_type = IMAGE_TYPE;
			can_delete = TRUE;
		}
		image_change_time = 0;
	}
}

void BreakBlock::Draw(float camera_work)const
{
	DrawRotaGraph(location.x + camera_work, location.y, 1, 0, image[image_type], TRUE, FALSE);
}