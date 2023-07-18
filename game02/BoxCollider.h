#pragma once
#include"define.h"

class BoxCollider
{
protected:

	DATA location;
	DATA radius;

public:

	bool HitBox(BoxCollider* bc);

	DATA GetLocation(void);
	DATA GetRadius(void);
};

