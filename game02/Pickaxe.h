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
    int image;

    bool can_throw_pickaxe_se;
    int angle;
    int angle_direction;
    bool can_throw;
    DATA speed;
    DATA old_location;
   
public:

    Pickaxe();
    void Delete();

    void Update(class Stage* stage);

    void Draw(float camera_work) const;

    bool GetCanThrow() { return can_throw; }

    void Pause(bool flg);

    void ThrowPickaxe(DATA location, DATA speed);
};