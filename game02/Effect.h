#pragma once
#include"define.h"

#define BREAK_BLOCK_IMAGE_TYPE 10


class Effect
{
private:

	DATA location;
	int image[BREAK_BLOCK_IMAGE_TYPE];
	int image_change_time;
	int image_type;
	int image_num;
	bool can_delete;

public:

	Effect(DATA location, int *image, int image_num);
	//~BreakBlock();

	void Update();
	void Draw(float camera_work) const;

	bool CanDelete() { return can_delete; }
};
