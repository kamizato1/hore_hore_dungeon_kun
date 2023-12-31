#include"dxlib.h"
#include"BoxCollider.h"

bool BoxCollider::HitBox(BoxCollider* bc)
{
    float sx1 = location.x - radius.x;
    float sx2 = location.x + radius.x;
    float sy1 = location.y - radius.y;
    float sy2 = location.y + radius.y;

    float dx1 = bc->location.x - bc->radius.x;
    float dx2 = bc->location.x + bc->radius.x;
    float dy1 = bc->location.y - bc->radius.y;
    float dy2 = bc->location.y + bc->radius.y;

    //矩形が重なっていれば当たり
    if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2)return TRUE;

    return FALSE;
}

DATA BoxCollider::GetLocation()const
{
    return location;
}

DATA BoxCollider::GetRadius()const
{
    return radius;
}