#pragma once

#include"define.h"

class FallingBlock
{
private:

	DATA location;
	int image;
	bool can_delete;
	float speed;
	float image_size;
	float image_angle;

public:

	FallingBlock(int image);
	void Delete();

	void Update();
	void Draw(float camera_work) const;

	bool CanDelete() { return can_delete; }
	float GetSize()const { return image_size; }
};
