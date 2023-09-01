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

    int life, time, remaining_time;
    float sway_width, sway_size;
    float max_sway_width;
    int screen_brightness;

    void ReStart();
    void Init();

public:

    GameMain();
    ~GameMain();

    //•`‰æˆÈŠO‚ÌXV‚ğÀ‘•‚·‚é
    void Update(Key* key) override;
    //•`‰æ‚ÉŠÖ‚·‚é‚±‚Æ‚ğÀ‘•‚·‚é
    void Draw() const override;
    AbstractScene* ChangeScene() override;

    void Sway();

};