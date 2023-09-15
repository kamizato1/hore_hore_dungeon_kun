#pragma once
#include"define.h"

class Ui
{
private:

    int life_image;
    int clear_image;
    int cross_image;
    int timer_image;

    int number_image[10];
    int item_image[ITEM_TYPE_NUM];
    int dark_item_image[ITEM_TYPE_NUM][2];
    int treasure_image[TREASURE_TYPE_NUM];
    int set_dark_item_image[6];
    

    float clear_image_size;
    int wait_time;
    bool end_clear_walk;
   
public:

    Ui();
    void Delete();
    bool Update(bool clear);
    void Draw(int time, int life, int pickaxe_flg, PLAYER_UI player_ui) const;
    bool MoveClearImage();
};