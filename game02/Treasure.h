#pragma once

#include"BoxCollider.h"
#include"Stage.h"
#include"define.h"


class Treasure : public BoxCollider
{
private:

    int image;
    DATA speed;
    TREASURE_TYPE treasure_type;
    
public:

    Treasure(int x, int y, int type, int image);
    void Update(class Stage* stage);
    void Draw(float camera_work) const;
};