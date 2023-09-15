#pragma once

#include"BoxCollider.h"
#include"define.h"


class Flag : public BoxCollider
{
private:

    bool can_delete;

public:

    Flag(DATA location);
    bool GetCanDelete() { return can_delete; }
};