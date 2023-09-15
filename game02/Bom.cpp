#include"DxLib.h"
#include"Bom.h"

#define BOM_COUNT 6
#define EXPLOSION_SIZE BLOCK_SIZE_X * 7
#define BOM_SIZE_CHANGE_TIME 6

Bom::Bom(DATA location, DATA speed)
{
    this->location = location;
    this->speed = speed;
    throw_flg = TRUE;
    radius = { 1,1 };
    if ((speed.x == 0) && (speed.y == 0))
    {
        throw_flg = FALSE;
        radius = { BLOCK_SIZE_X / 2, BLOCK_SIZE_Y / 2 };
    }
    can_delete = FALSE;
    angle = 0;
    angle_direction = 3;
    if (speed.x < 0)angle_direction = -3;
    count = FPS * BOM_COUNT;
    bom_size = 1;
    bom_size_add = 0.1;
    bom_size_change_time = BOM_SIZE_CHANGE_TIME * 2;
    old_hit = FALSE;
}

void Bom::Update(Stage* stage)
{
    if (--bom_size_change_time == 0)
    {
        bom_size_change_time = BOM_SIZE_CHANGE_TIME;
        bom_size += bom_size_add;
        if (bom_size >= 1.3)bom_size_add = -0.1;
        else if (bom_size <= 1.0)
        {
            bom_size_add = 0.1;
            bom_size_change_time = BOM_SIZE_CHANGE_TIME * 2;
        }
    }

    if (throw_flg)
    {
        speed.y += GRAVITY_POWER;
        location.y += speed.y;

        location.x += speed.x;

        angle += angle_direction;

        if (stage->HitBlock(this).flg)can_delete = TRUE;
    }
    else
    {
        if ((!stage->HitBlock(this).flg) && (!stage->HitTreasure(this, FALSE).flg) && (!stage->HitBom(this, TRUE).flg))location.y += 1;
        if ((stage->HitBlock(this).flg) || (stage->HitTreasure(this, FALSE).flg) || (stage->HitBom(this, TRUE).flg))
        {
            int y = location.y / BLOCK_SIZE_Y;
            location.y = (y * BLOCK_SIZE_Y) + (radius.y);
        }

        if (--count <= 0)can_delete = TRUE;
    }
}

bool Bom::HitExplosion(BoxCollider* bc)
{  
    radius = { EXPLOSION_SIZE / 2, EXPLOSION_SIZE / 2 };
    bool flg = HitBox(bc);
    if (throw_flg)radius = { 1,1 };
    else radius = { BLOCK_SIZE_X / 2, BLOCK_SIZE_Y / 2 };
    return flg;
}

GET_DRAW_BOM Bom::GetDrawBom()const
{
    GET_DRAW_BOM get_draw_bom;
    get_draw_bom.location = location;
    get_draw_bom.throw_flg = throw_flg;
    get_draw_bom.count = count;
    get_draw_bom.angle = angle;
    get_draw_bom.bom_size = bom_size;
    return get_draw_bom;
}
