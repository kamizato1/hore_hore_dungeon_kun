#pragma once

#include"Key.h"
#include"Player.h"
#include"Stage.h"
#include"AbstractScene.h"
#include"Ui.h"
#include"define.h"

class GameMain : public AbstractScene
{
private:

    bool stop;
    Stage* stage;
    Player* player;
    int back_ground_image[3];

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