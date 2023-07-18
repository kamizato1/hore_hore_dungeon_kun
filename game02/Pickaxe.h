#pragma once

#include"BoxCollider.h"
#include"Stage.h"
#include"define.h"

class Pickaxe : public BoxCollider
{
private:

    int image;
    int angle;
    int angle_direction;
    bool can_delete;
    DATA speed;
    DATA old_location;
    int hit_pickaxe_se;

public:

    Pickaxe(DATA location, DATA speed);

    void Update(Stage* stage);
    void Draw(float camera_work) const;

    bool CanDelete() { return can_delete; }
};