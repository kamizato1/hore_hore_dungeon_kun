#pragma once

#include"BoxCollider.h"
#include"Stage.h"
#include"define.h"


class Treasure : public BoxCollider
{
private:

    int image;
    DATA speed;
    TREASURE_TYPE type;
    
public:

    Treasure(int x, int y, TREASURE_TYPE type, int image);
    void Update(class Stage* stage);
    void Draw(float camera_work) const;
    TREASURE_TYPE GetTreasureType() { return type; }
};