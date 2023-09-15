#pragma once

#include"BoxCollider.h"
#include"Stage.h"
#include"define.h"

struct GET_DRAW_BOM
{
    DATA location;
    bool throw_flg;
    int count;
    int angle;
    float bom_size;
};

class Bom : public BoxCollider
{
private:

    int angle;
    int angle_direction;
    float bom_size;
    float bom_size_add;
    int bom_size_change_time;
    DATA speed;
    bool can_delete;
    bool throw_flg;
    int count;
    bool old_hit;

public:

    Bom(DATA location, DATA speed);
    void Update(class Stage* stage);
    bool HitExplosion(BoxCollider* bc);
    bool GetCanDelete() { return can_delete; }
    void SetCanDelete(bool flg) { can_delete = flg; }
    GET_DRAW_BOM GetBomDraw()const;

};