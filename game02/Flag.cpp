#include"DxLib.h"
#include"Flag.h"

Flag::Flag(DATA location)
{
    radius = { 10 ,10 };
    this->location = location;
    can_delete = FALSE;
}