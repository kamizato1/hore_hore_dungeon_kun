#pragma once

#include"BoxCollider.h"
#include"Key.h"
#include"Stage.h"
#include"Cursor.h"
#include"define.h"

#define R_STICK_ANGLE_RECORD_NUM 20
#define L_STICK_ANGLE_RECORD_NUM 15

#define PICKAXE_SET_TIME 10
#define BLOCK_SET_TIME 300
#define BOM_SET_TIME 20

class Player : public BoxCollider
{
private:

    int image[2][5];
    int item_image[ITEM_TYPE_NUM];
    int sign_image;
    int frame_image;
    int set_image[10];

    int jump_se;
    int get_treasure_se;
    int die_se;
    

    int now_item_set_time[ITEM_TYPE_NUM];
    int item_set_time[ITEM_TYPE_NUM] = { PICKAXE_SET_TIME , BLOCK_SET_TIME ,BOM_SET_TIME };
    bool pickaxe_flg;
    bool can_throw, die;
    DATA speed;
    DATA throw_speed;
    DATA r_stick_angle_record[R_STICK_ANGLE_RECORD_NUM];
    float speed_x_record[L_STICK_ANGLE_RECORD_NUM];
    int item_type;
    int treasure_num[TREASURE_TYPE_NUM];
    int break_block_num;
    Cursor* cursor;
    bool clear;
    bool can_use_item[ITEM_TYPE_NUM];

    //テスト
    
    int image_type; //アニメーション
    int image_change_time; //アニメーション切り替え時間
    int direction;

    //ここまで


public:

    Player();
    void Delete();
    void Update(Key* key, Stage* stagebase);
    void Draw(float camera_work) const;

    void MoveX(Key* key, Stage* stagebase);
    void MoveY(Key* key, Stage* stagebase);
    bool GetPlayerDie() { return die; }
    void SetPlayerDie(bool flg) { die = flg; }
    void Init();
    bool GetClear() { return clear; }
    int GetItemType()const { return item_type; }
    int* GetTreasureNum() { return treasure_num; }
    PLAYER_UI GetPlayerUi()const;

};