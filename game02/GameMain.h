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
    bool change_scene;
  
    void ReStart();
    void Init();
    void Sway();
   
public:

    GameMain(int stage_num, int stage_width);
    ~GameMain();

    void Update(Key* key) override; //描画以外の更新を実装する
    void Draw() const override; //描画に関することを実装する

    AbstractScene* ChangeScene() override;
};