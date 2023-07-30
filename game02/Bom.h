#pragma once

#include"BoxCollider.h"
#include"Stage.h"
#include"define.h"

class Bom : public BoxCollider
{
private:

    int image;
    int angle;
    int angle_direction;
    
    DATA speed;
    bool can_delete;
    bool throw_flg;

    int count;

public:

    Bom(DATA location, DATA speed);

    void Update(class Stage* stage);
    void Draw(float camera_work) const;

    bool CanDelete() { return can_delete; }
};