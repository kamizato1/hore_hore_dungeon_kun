#include"DxLib.h"
#include"GameMain.h"
#include"Stage.h"
#include"SampleStage.h"

#define TIME 100

GameMain::GameMain()
{
    stagebase = new Stage();
    player = new Player();
    ui = new Ui();
    back_ground_image[0] = LoadGraph("images/background01.png");
    back_ground_image[1] = LoadGraph("images/background02.png");
    back_ground_image[2] = LoadGraph("images/background03.png");
    stop = FALSE;
    time = 0;

}
GameMain::~GameMain()
{
    delete player;
    delete stagebase;
    delete ui;
}

void GameMain::Update(Key* key)
{
    if (key->KeyDown(START))stop = !stop;

    if (!stop)
    {
        time++;
        stagebase->Update();
        player->Update(key, stagebase);
    }

    if (TIME - (time / FPS) < 0)time = 0;

    if (player->GetLocation().y > SCREEN_HEIGHT + 15) stop = TRUE;
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

    ui->Draw(TIME - (time / FPS));
}

AbstractScene* GameMain::ChangeScene()
{
    return this;
}