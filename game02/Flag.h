#pragma once

#include"BoxCollider.h"
#include"define.h"


class Flag : public BoxCollider
{
private:

    int image;
    bool can_delete;

public:

    Flag(DATA location);
    void Update(BoxCollider* bc);
    void Draw(float camera_work) const;
    bool GetCanDelete() { return can_delete; }
};