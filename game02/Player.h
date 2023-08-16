#pragma once

#include"BoxCollider.h"
#include"Key.h"
#include"StageBase.h"
#include"define.h"

#define R_STICK_ANGLE_RECORD_NUM 20
#define L_STICK_ANGLE_RECORD_NUM 15

class Player : public BoxCollider
{
private:

    int image;
   
    DATA speed;
    DATA throw_speed;
    DATA r_stick_angle_record[R_STICK_ANGLE_RECORD_NUM];
    float speed_x_record[L_STICK_ANGLE_RECORD_NUM];

    DATA cursor_location;
    int cursor_image;
    bool can_use_item;

    ITEM_TYPE item_type;
    int item_num[3];

public:

    Player();

    void Update(Key* key, StageBase* stagebase);
    void Draw(float camera_work) const;

    void MoveX(Key* key, StageBase* stagebase);
    void MoveY(Key* key, StageBase* stagebase);
    void Cursor();
};