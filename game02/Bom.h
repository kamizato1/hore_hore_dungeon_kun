#pragma once

#include"BoxCollider.h"
#include"Stage.h"
#include"define.h"

class Bom : public BoxCollider
{
private:

    int image;
    int frame_image;
    int angle;
    int angle_direction;
    float bom_size;
    float bom_size_add;
    int bom_size_change_time;
    DATA speed;
    bool can_delete;
    bool throw_flg;
    int count;
    int number_image[6];
    bool old_hit;

public:

    Bom(DATA location, DATA speed);
    void Delete();
    void Update(class Stage* stage);
    void Draw(float camera_work) const;
    bool HitExplosion(BoxCollider* bc);
    bool GetCanDelete() { return can_delete; }
    void SetCanDelete(bool flg) { can_delete = flg; }


};