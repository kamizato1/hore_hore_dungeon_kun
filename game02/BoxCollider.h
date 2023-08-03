#pragma once
#include"define.h"

class BoxCollider
{
protected:

	DATA location;
	DATA radius;

public:

	bool HitBox(BoxCollider* bc);
	bool HitBox(DATA location, DATA radius);

	DATA GetLocation(void);
	DATA GetRadius(void);
};

