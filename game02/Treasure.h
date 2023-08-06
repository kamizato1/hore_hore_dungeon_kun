#pragma once

#include"BoxCollider.h"
#include"Stage.h"
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

    Treasure(int x, int y, TREASURE_TYPE type, int image);
    void Update(class Stage* stage);
    void Draw(float camera_work) const;
    bool HitDamage(bool hit_type, Stage* stage);
    bool GetCanDelete() { return can_delete; }
    void SetOldHit(bool flg) { old_hit = flg; }
    TREASURE_TYPE GetTreasureType() { return type; }
};