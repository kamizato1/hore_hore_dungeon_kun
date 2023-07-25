#include"DxLib.h"
#include"GameMain.h"

GameMain::GameMain()
{
    stage = new Stage();
    player = new Player();
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
    
    stage->Draw(camera_work);
    player->Draw(camera_work);
}

AbstractScene* GameMain::ChangeScene()
{
    return this;
}