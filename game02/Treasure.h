#pragma once

#include"BoxCollider.h"
#include"Stage.h"
#include"define.h"

class Treasure : public BoxCollider
{
private:

    bool old_hit;
    DATA speed;
    TREASURE_TYPE type;
    bool can_delete;
    
public:

    Treasure(DATA location, int type);
    void Update(class Stage* stage);
   
    bool GetCanDelete() { return can_delete; }
    void SetOldHit(bool flg) { old_hit = flg; }
    bool GetOldHit(Stage* stage);
    TREASURE_TYPE GetTreasureType() const{ return type; }
};