#include"DxLib.h"
#include"Flag.h"

Flag::Flag(DATA location)
{
    radius = { 10 ,10 };
    this->location = location;
    can_delete = FALSE;
    image = LoadGraph("images/Flag/flag.png");
}

void Flag::Update()
{
}

void Flag::Draw(float camera_work) const
{
    DrawRotaGraph(location.x + camera_work, location.y, 1, 0, image, TRUE);
}