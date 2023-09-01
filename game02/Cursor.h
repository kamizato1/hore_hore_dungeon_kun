#pragma once

#include"BoxCollider.h"
#include"define.h"

class Cursor : public BoxCollider
{
private:

    int image;
    int cursor_sign_x;
    int cursor_sign_y;
    bool hit_player;

public:

    Cursor(DATA location);

    void Update(BoxCollider* bc, DATA r_stick_angle);
    void Draw(float camera_work) const;
};