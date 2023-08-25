#pragma once

#include"BoxCollider.h"
#include"Key.h"
#include"Stage.h"
#include"Cursor.h"
#include"define.h"

#define R_STICK_ANGLE_RECORD_NUM 20
#define L_STICK_ANGLE_RECORD_NUM 15

class Player : public BoxCollider
{
private:

    int image;
    bool can_throw, die;
    DATA speed;
    DATA throw_speed;
    DATA r_stick_angle_record[R_STICK_ANGLE_RECORD_NUM];
    float speed_x_record[L_STICK_ANGLE_RECORD_NUM];
    ITEM_TYPE item_type;
    int item_num[3];
    Cursor* cursor;

    //�e�X�g
    
    int image_test[4]; //�v���C���[�A�j���[�V�����摜
    int anime; //�A�j���[�V����
    int anime_time; //�A�j���[�V�����؂�ւ�����

    //�����܂�


public:

    Player();

    void Update(Key* key, Stage* stagebase);
    void Draw(float camera_work) const;

    void MoveX(Key* key, Stage* stagebase);
    void MoveY(Key* key, Stage* stagebase);
    bool GetPlayerDie() { return die; }
    void SetPlayerDie(bool flg) { die = flg; }
    void Init();
};