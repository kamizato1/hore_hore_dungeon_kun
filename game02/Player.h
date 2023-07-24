#pragma once

#include"BoxCollider.h"
#include"Key.h"
#include"Stage.h"
#include"Pickaxe.h"
#include"define.h"

#define R_STICK_ANGLE_RECORD_NUM 15
#define SPEED_X_RECORD_NUM 15

class Player : public BoxCollider
{
private:

    Pickaxe* pickaxe;

    int image;
    float gravity;
    float jump_speed;
   
    DATA speed;
    DATA pickaxe_speed;
    DATA r_stick_angle_record[R_STICK_ANGLE_RECORD_NUM];
    float speed_x_record[SPEED_X_RECORD_NUM];

    DATA cursor_location;
    int cursor_image;

    bool can_use_item;

    ITEM_TYPE item_type;
    
public:

    Player();

    void Update(Key* key, Stage* stage);
    void Draw(float camera_work) const;

    void MoveX(Key* key, Stage* stage);
    void MoveY(Key* key, Stage* stage);
};