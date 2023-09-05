#pragma once
#include "AbstractScene.h"

#define TREASURE_NUM 4

class Result : public AbstractScene
{
private:

    int score;
    int treasure_num[TREASURE_NUM];
    int treasure_score[TREASURE_NUM];
    int treasure_price[TREASURE_NUM];

    int stamp_image;
    int sign_image[3];
    int treasure_image[TREASURE_NUM];
    int map_image;
    int score_image;
    int back_ground_image[3];
    int number_image[10];

    int wait_time;

    float score_image_size;
    float score_image_angle;

    float back_ground_image_x[3];

    float stamp_image_size;
    
    bool end_add_score;
    bool end_move_score;
    bool end_move_stamp;
    bool stamp_flg;
    bool skip;
    bool new_record;

    //遷移するのか
    bool transition;

public:

    Result(int stage_num, int* treasure_num);//壊したブロックの数、時間、持っているブロックの数,宝の種類と種類    
    ~Result(); //デストラクタ

    void Update(Key* key) override;//描画以外の更新を実装する
    void Draw() const override;//描画に関することを実装する
    AbstractScene* ChangeScene() override;//シーン切り替え

    void MoveScore();
    void AddScore();
    void MoveStamp();
};

