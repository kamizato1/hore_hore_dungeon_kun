#pragma once

class Ui
{
private:

    int life_image;
    int number_image[10];

public:

    Ui();
    void Update();
    void Draw(int time, int life) const;
};