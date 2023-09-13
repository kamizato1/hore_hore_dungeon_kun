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
    int item_image[3];
    int timer_image;
    int block_image[2];
    int sign_image[2];
    int treasure_image[TREASURE_TYPE_NUM];
    bool end_clear_walk;
   
public:

    Ui();
    bool Update(bool clear);
    void Draw(int time, int life, PLAYER_UI player_ui) const;
    bool MoveClearImage();
};