#pragma once

#include"BoxCollider.h"
#include"StageBase.h"
#include"define.h"


class Treasure : public BoxCollider
{
private:

    int image;
    bool old_hit;
    DATA speed;
    TREASURE_TYPE type;
    bool can_delete;
    
public:

    Treasure(DATA location, int type);
    void Update(class StageBase* stagebase);
    void Draw(float camera_work) const;
    bool HitDamage(bool hit_type, StageBase* stagebase);
    bool GetCanDelete() { return can_delete; }
    void SetOldHit(bool flg) { old_hit = flg; }
    TREASURE_TYPE GetTreasureType() { return type; }
};