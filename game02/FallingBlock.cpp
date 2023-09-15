#include"DxLib.h"
#include"FallingBlock.h"

FallingBlock::FallingBlock()
{
	location.x = GetRand(SCREEN_WIDTH);
	location.y = -GetRand(50);
	speed = GetRand(15) + 1;
	image_size = (speed / 10);
	can_delete = FALSE;
	image_angle = GetRand(100);
}

void FallingBlock::Update()
{
	location.y += speed;
	if (location.y > (SCREEN_HEIGHT + 100))can_delete = TRUE;
}

GET_DRAW_FALLING_BLOCK FallingBlock::GetDrawFallingBlock()const
{
	GET_DRAW_FALLING_BLOCK get_draw_falling_block;
	get_draw_falling_block.location = location;
	get_draw_falling_block.image_size = image_size;
	get_draw_falling_block.image_angle = image_angle;
	return get_draw_falling_block;
}


//void FallingBlock::Draw(float camera_work)const
//{
//	DrawRotaGraph(location.x, location.y, image_size, image_angle, image, TRUE, FALSE);
//}