#pragma once

#include"Key.h"
#include"Player.h"
#include"Stage.h"
#include"AbstractScene.h"
#include"Pause.h"
#include"Ui.h"
#include"define.h"

class GameMain : public AbstractScene
{
private:

    bool stop;
    bool sway_flg;
    bool die, clear;

    Stage* stage;
    Player* player;
    Ui* ui;
    Pause* pause;

    int max_scroll;
    int life, time, remaining_time;
    float sway_width, sway_size;
    float max_sway_width;
    int screen_brightness;
    int stage_num;
    int wait_time;
    int stage_clear_image;
    float stage_clear_image_size;
    bool end_clear_walk;
    bool end_move_stage_clear;

    void ReStart();
    void Init();
    void Sway();
    void MoveStageClear();

public:

    GameMain(int stage_num, int stage_width);
    ~GameMain();

    void Update(Key* key) override; //•`‰æˆÈŠO‚ÌXV‚ğÀ‘•‚·‚é
    void Draw() const override; //•`‰æ‚ÉŠÖ‚·‚é‚±‚Æ‚ğÀ‘•‚·‚é

    AbstractScene* ChangeScene() override;
};