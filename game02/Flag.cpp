#include"DxLib.h"
#include"Flag.h"

Flag::Flag(DATA location)
{
    radius = { BLOCK_SIZE_X / 2 ,BLOCK_SIZE_Y / 2 };
    this->location = location;
    can_delete = FALSE;
    image = LoadGraph("images/flag.png");
}

void Flag::Update(BoxCollider* bc)
{
    if (HitBox(bc))can_delete = TRUE;
}

void Flag::Draw(float camera_work) const
{
    DrawRotaGraph(location.x + camera_work, location.y, 1, 0, image, TRUE);
}