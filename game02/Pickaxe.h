#pragma once

#include"BoxCollider.h"
#include"Stage.h"
#include"Player.h"
#include"define.h"

class Pickaxe : public BoxCollider
{
private:

    int break_pickaxe_se;
    int throw_pickaxe_se;
    int hit_pickaxe_se;

    int can_throw_pickaxe_se;

    int image;
    int angle;
    int angle_direction;
    bool can_delete;
    DATA speed;
    DATA old_location;
   

public:

    Pickaxe(DATA location, DATA speed, int image, int throw_pickaxe_se, int hit_pickaxe_se, int break_pickaxe_se);
    ~Pickaxe();

    void Update(class Stage* stage);
    void Draw(float camera_work) const;

    bool GetCanDelete() { return can_delete; }

    void Pause(bool flg);
};