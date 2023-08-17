#include"DxLib.h"
#include"GameMain.h"
#include"Stage.h"
#include"SampleStage.h"

GameMain::GameMain()
{
    stagebase = new Stage();
    player = new Player();
    back_ground_image[0] = LoadGraph("images/background01.png");
    back_ground_image[1] = LoadGraph("images/background02.png");
    back_ground_image[2] = LoadGraph("images/background03.png");
    stop = FALSE;
}
GameMain::~GameMain()
{
    delete player;
    delete stagebase;
}

void GameMain::Update(Key* key)
{
    if (key->KeyDown(START))stop = !stop;

    if (!stop)
    {
        stagebase->Update();
        player->Update(key, stagebase);
    }
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
    stagebase->Draw1(camera_work);
    player->Draw(camera_work);
    stagebase->Draw2(camera_work);

    DrawFormatString(0, 0, 0xffffff, "%f", camera_work);
}

AbstractScene* GameMain::ChangeScene()
{
    return this;
}