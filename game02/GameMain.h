#pragma once

#include <vector>
#include"Key.h"
#include"Player.h"
#include"Stage.h"
#include"AbstractScene.h"
#include"Pause.h"
#include"Ui.h"
#include"FallingBlock.h"
#include"define.h"

class GameMain : public AbstractScene
{
private:

    bool stop;
    bool sway_flg;

    Stage* stage;
    Player* player;
    Ui* ui;
    Pause* pause;

    std::vector<FallingBlock>fallingblock;

    int back_ground_image[3];
    int falling_block_image;
    int life, time, remaining_time;
    float sway_width, sway_size;
    float max_sway_width;

public:

    GameMain();
    ~GameMain();

    //描画以外の更新を実装する
    void Update(Key* key) override;
    //描画に関することを実装する
    void Draw() const override;
    AbstractScene* ChangeScene() override;

    void Sway();

};