#pragma once
#include "AbstractScene.h"

class Result : public AbstractScene
{
private:

    int roll_score_se;
    int set_score_se;
    int result_bgm;
    int drum_roll_se;
    int drum_se;
    int stamp_se;
    int decision_se;

    int stamp_image;
    int sign_image[3];
    int treasure_image[TREASURE_TYPE_NUM];
    int map_image;
    int score_image;
    int back_ground_image[3];
    int number_image[10];
    

    int score;
    int treasure_num[TREASURE_TYPE_NUM];
    int treasure_score[TREASURE_TYPE_NUM];
    int treasure_price[TREASURE_TYPE_NUM];
    int treasure_add_score[TREASURE_TYPE_NUM];

    int stage_num;

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
    void Delete() override;
    void Update(Key* key) override;//描画以外の更新を実装する
    void Draw() const override;//描画に関することを実装する
    AbstractScene* ChangeScene() override;//シーン切り替え

    void MoveScore();
    void AddScore();
    void MoveStamp();
};

