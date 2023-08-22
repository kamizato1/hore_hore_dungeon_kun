#include"DxLib.h"
#include"GameMain.h"
#include"Stage.h"
#include"SampleStage.h"

#define TIME 100
#define MAX_SWAY_WIDTH 3

GameMain::GameMain()
{
    stage = new Stage();
    player = new Player();
    ui = new Ui();
    back_ground_image[0] = LoadGraph("images/background01.png");
    back_ground_image[1] = LoadGraph("images/background02.png");
    back_ground_image[2] = LoadGraph("images/background03.png");
    stop = FALSE;
    time = 0;

    sway_width = 0;
    sway_size = 0.8;
}
GameMain::~GameMain()
{
    delete player;
    delete stage;
    delete ui;
}

void GameMain::Update(Key* key)
{
    if (key->KeyDown(START))stop = !stop;

    if (!stop)
    {
        time++;
        stage->Update();
        player->Update(key, stage);
    }

    if (TIME - (time / FPS) < 0)time = 0;

    if (player->GetLocation().y > SCREEN_HEIGHT + 15) stop = TRUE;
    Sway();
}

void GameMain::Draw() const
{
    float camera_work = 0;
    if (player->GetLocation().x >= 350)camera_work = -player->GetLocation().x + 350;
    camera_work += sway_width;

    SetDrawBright(150, 150, 150);
    DrawGraph((camera_work / 10), 0, back_ground_image[2], TRUE);
    DrawGraph((camera_work / 7), 0, back_ground_image[1], TRUE);
    DrawGraph((camera_work / 5), 0, back_ground_image[0], TRUE);
    SetDrawBright(255, 255, 255);
    stage->Draw1(camera_work);
    player->Draw(camera_work);
    stage->Draw2(camera_work);

    ui->Draw(TIME - (time / FPS));
}

float GameMain::Sway()
{
    sway_width += sway_size;
    if ((sway_width > MAX_SWAY_WIDTH) || (sway_width < -MAX_SWAY_WIDTH))sway_size = -sway_size;

    return sway_width;
}

AbstractScene* GameMain::ChangeScene()
{
    return this;
}

