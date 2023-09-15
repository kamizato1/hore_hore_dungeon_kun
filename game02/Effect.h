#pragma once
#include"define.h"

struct GET_DRAW_EFFECT
{
	DATA location;
	int effect_type;
	int item_type;
	int image_type;
};

class Effect
{
private:

	DATA location;
	int image_change_time;
	int image_type;
	int effect_type;
	int item_type;
	bool can_delete;

public:

	Effect(DATA location, int effect_type, int item_type);
	void Update();
	bool CanDelete() { return can_delete; }
	GET_DRAW_EFFECT GetDrawEffect()const;
};
