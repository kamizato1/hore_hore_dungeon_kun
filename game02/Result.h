#pragma once
#include "AbstractScene.h"

#define TREASURE_NUM 3

class Result : public AbstractScene
{
private:

    int score;
    int map_image;
    int score_image;
    int back_ground_image[3];
    int number_image[10];

    float score_image_size;
    float score_image_angle;
    float move_back_ground_image[3];

    int treasure_num[TREASURE_NUM];

    bool end_move_score;

    //遷移するのか
    bool transition;

public:

    Result(int block_break,int time ,int item_block);//壊したブロックの数、時間、持っているブロックの数,宝の種類と種類    
    ~Result(); //デストラクタ

    void Update(Key* key) override;//描画以外の更新を実装する
    void Draw() const override;//描画に関することを実装する
    AbstractScene* ChangeScene() override;//シーン切り替え

    void MoveScore();
};

