#include"DxLib.h"
#include"FallingBlock.h"

FallingBlock::FallingBlock(DATA location, int image, float speed, float image_size)
{
	this->location = location;
	can_delete = FALSE;
	this->image = image;
	this->speed = speed;
	this->image_size = image_size;
	image_angle = GetRand(100);
}

void FallingBlock::Update()
{
	location.y += speed;
	if (location.y > (SCREEN_HEIGHT + 100))can_delete = TRUE;
}

void FallingBlock::Draw(float camera_work)const
{
	DrawRotaGraph(location.x, location.y, image_size, image_angle, image, TRUE, FALSE);
}