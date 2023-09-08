#pragma once

class Ui
{
private:

    int life_image;
    int number_image[10];
    int clear_image;
    float clear_image_size;
    int wait_time;
    int item_image[3];
    bool end_clear_walk;
   
public:

    Ui();
    bool Update(bool clear);
    void Draw(int time, int life, int item_type) const;
    bool MoveClearImage();
};