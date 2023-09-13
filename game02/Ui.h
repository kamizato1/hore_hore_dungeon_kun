#pragma once
#include"define.h"

class Ui
{
private:

    int life_image;
    int number_image[10];
    int clear_image;
    float clear_image_size;
    int wait_time;
    int item_image[ITEM_TYPE_NUM];
    int timer_image;
    int dark_item_image[ITEM_TYPE_NUM][2];
    int treasure_image[TREASURE_TYPE_NUM];
    bool end_clear_walk;
   
public:

    Ui();
    bool Update(bool clear);
    void Draw(int time, int life, int pickaxe_flg, PLAYER_UI player_ui) const;
    bool MoveClearImage();
};