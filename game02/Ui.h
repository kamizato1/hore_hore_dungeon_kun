#pragma once

class Ui
{
private:

    int life_image;
    int number_image[10];

    int life;

public:

    Ui();
    void Update();
    void Draw(int time) const;
};