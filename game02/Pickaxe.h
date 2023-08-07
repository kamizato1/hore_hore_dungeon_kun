#pragma once

#include"BoxCollider.h"
#include"Stage.h"
#include"define.h"

class Pickaxe : public BoxCollider
{
private:

    int image;
    int se;
    int angle;
    int angle_direction;
    bool can_delete;
    DATA speed;
    DATA old_location;
   

public:

    Pickaxe(DATA location, DATA speed, int image, int se);

    void Update(Stage* stage);
    void Draw(float camera_work) const;

    bool GetCanDelete() { return can_delete; }
};