#include"dxlib.h"
#include"BoxCollider.h"

bool BoxCollider::HitBox(BoxCollider* bc)
{
    float sx1 = location.x - radius.x - 1;
    float sx2 = location.x + radius.x + 1;
    float sy1 = location.y - radius.y - 1;
    float sy2 = location.y + radius.y + 1;

    float dx1 = bc->location.x - bc->radius.x;
    float dx2 = bc->location.x + bc->radius.x;
    float dy1 = bc->location.y - bc->radius.y;
    float dy2 = bc->location.y + bc->radius.y;

    //‹éŒ`‚ªd‚È‚Á‚Ä‚¢‚ê‚Î“–‚½‚è
    if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2)return TRUE;

    return FALSE;
}

DATA BoxCollider::GetLocation()
{
    return location;
}

DATA BoxCollider::GetRadius()
{
    return radius;
}