#include"DxLib.h"
#include"GameMain.h"

GameMain::GameMain()
{
    stage = new Stage();
    player = new Player();
    back_ground_image[0] = LoadGraph("images/background01.png");
    back_ground_image[1] = LoadGraph("images/background02.png");
    back_ground_image[2] = LoadGraph("images/background03.png");
}
GameMain::~GameMain()
{
    delete player;
    delete stage;
}

void GameMain::Update(Key* key)
{
    stage->Update();
    player->Update(key, stage);
}

void GameMain::Draw() const
{
    float camera_work = 0;
    if (player->GetLocation().x >= 350)camera_work = -player->GetLocation().x + 350;
    
    SetDrawBright(150, 150, 150);
    DrawGraph((camera_work / 10), 0, back_ground_image[2], TRUE);
    DrawGraph((camera_work / 7), 0, back_ground_image[1], TRUE);
    DrawGraph((camera_work / 5), 0, back_ground_image[0], TRUE);
    SetDrawBright(255, 255, 255);
    stage->Draw(camera_work);
    player->Draw(camera_work);
}

AbstractScene* GameMain::ChangeScene()
{
    return this;
}