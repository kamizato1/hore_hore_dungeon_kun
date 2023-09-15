#include"DxLib.h"
#include"Effect.h"

#define EFFECT_IMAGE_NUM 10
#define IMAGE_CHANGE_TIME 2

Effect::Effect(DATA location, int effect_type, int item_type)
{
	this->item_type = item_type;
	this->effect_type = effect_type;
	this->location = location;
	image_change_time = 0;
	can_delete = FALSE;
	image_type = 0;
}

void Effect::Update()
{
	if (++image_change_time > IMAGE_CHANGE_TIME)
	{
		if (++image_type >= EFFECT_IMAGE_NUM)can_delete = TRUE;
		image_change_time = 0;
	}
}

GET_DRAW_EFFECT Effect::GetDrawEffect()const
{
	GET_DRAW_EFFECT get_draw_effect;
	get_draw_effect.location = location;
	get_draw_effect.effect_type = effect_type;
	get_draw_effect.item_type = item_type;
	get_draw_effect.image_type = image_type;
	return get_draw_effect;
}