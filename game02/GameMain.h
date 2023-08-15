#pragma once

#include"Key.h"
#include"Player.h"
#include"StageBase.h"
#include"AbstractScene.h"
#include"Ui.h"
#include"define.h"

class GameMain : public AbstractScene
{
private:

    bool stop;

    StageBase* stagebase;
    Player* player;
    Ui* ui;

    int back_ground_image[3];
    int life;
    int time;

public:

    GameMain();
    ////デストラクタ
    ~GameMain();

    //描画以外の更新を実装する
    void Update(Key* key) override;
    //描画に関することを実装する
    void Draw() const override;
    AbstractScene* ChangeScene() override;

};