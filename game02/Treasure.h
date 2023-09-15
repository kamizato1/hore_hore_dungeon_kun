#pragma once

#include"BoxCollider.h"
#include"Stage.h"
#include"define.h"

class Treasure : public BoxCollider
{
private:

    int image;
    int set_image[TREASURE_TYPE_NUM];
    bool old_hit;
    DATA speed;
    TREASURE_TYPE type;
    bool can_delete;
    
public:

    Treasure(DATA location, int type);
    void Delete();
    void Update(class Stage* stage);
    void Draw(float camera_work) const;
    
    bool GetCanDelete() { return can_delete; }
    void SetOldHit(bool flg) { old_hit = flg; }
    bool GetOldHit(Stage* stage);
    TREASURE_TYPE GetTreasureType() { return type; }
};