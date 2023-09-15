#pragma once
#include"define.h"

struct GET_DRAW_FALLING_BLOCK
{
	DATA location;
	float image_size;
	float image_angle;
};

class FallingBlock
{
private:

	DATA location;
	
	bool can_delete;
	float speed;
	float image_size;
	float image_angle;

public:

	FallingBlock();

	void Update();

	bool CanDelete() { return can_delete; }
	float GetSize()const { return image_size; }
	GET_DRAW_FALLING_BLOCK GetDrawFallingBlock()const;
};
