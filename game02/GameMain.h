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

    StageBase* stage;
    Player* player;
    Ui* ui;

    int back_ground_image[3];
    int life, time;
    float sway_width, sway_size;

public:

    GameMain();
    ~GameMain();

    //•`‰æˆÈŠO‚ÌXV‚ğÀ‘•‚·‚é
    void Update(Key* key) override;
    //•`‰æ‚ÉŠÖ‚·‚é‚±‚Æ‚ğÀ‘•‚·‚é
    void Draw() const override;
    AbstractScene* ChangeScene() override;

    float Sway();

};