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

    int stage_bgm;
    int stage_clear_bgm;
    int pause_se;
    int earthquake_se;

    int max_scroll;
    int life, time, remaining_time;
    float sway_width, sway_size;
    float max_sway_width;
    int screen_brightness;
    int stage_num;
    bool change_result_scene;
    bool change_game_over_scene;
  
    void ReStart();
    void Init();
    void Sway();
    void Pause(bool flg);
   
public:

    GameMain(int stage_num);
    ~GameMain();

    void Delete() override {};
    void Update(Key* key) override; //•`‰æˆÈŠO‚ÌXV‚ğÀ‘•‚·‚é
    void Draw() const override; //•`‰æ‚ÉŠÖ‚·‚é‚±‚Æ‚ğÀ‘•‚·‚é

    AbstractScene* ChangeScene() override;
};