#include"DxLib.h"
#include"FallingBlock.h"

FallingBlock::FallingBlock(int image)
{
	location.x = GetRand(SCREEN_WIDTH);
	location.y = -GetRand(50);
	speed = GetRand(15) + 1;
	image_size = (speed / 10);
	can_delete = FALSE;
	this->image = image;
	image_angle = GetRand(100);
}

void FallingBlock::Delete()
{
	DeleteGraph(image);
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