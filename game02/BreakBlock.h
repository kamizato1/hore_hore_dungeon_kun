#pragma once
#include"define.h"

#define IMAGE_TYPE 10


class BreakBlock
{
private:

	DATA location;
	int image[IMAGE_TYPE];
	int image_change_time;
	int image_type;
	bool can_delete;

public:

	BreakBlock(DATA location);
	//~BreakBlock();

	void Update();
	void Draw(float camera_work) const;

	bool CanDelete() { return can_delete; }
};
