#include"DxLib.h"
#include"GameMain.h"

GameMain::GameMain()
{
    stage = new Stage();
    player = new Player();
    ui = new Ui();
    for (int i = 0; i < 15; i++)camera_work_record[i] = 0;
}
GameMain::~GameMain()
{
    delete player;
    delete stage;
    delete ui;
}

void GameMain::Update(Key* key)
{
    stage->Update();
    player->Update(key, stage);
    
    /*float all_camera_work_record_calculation = 0;
    float old_camera_work;

    float now_camera_work = 0;
    if (player->GetLocation().x >= 350)now_camera_work = -player->GetLocation().x + 350;

    for (int i = 0; i < 20; i++)
    {
        old_camera_work = camera_work_record[i];
        camera_work_record[i] = now_camera_work;
        now_camera_work = old_camera_work;
        all_camera_work_record_calculation += camera_work_record[i];
    }

    camera_work = (all_camera_work_record_calculation / 20);*/
}

void GameMain::Draw() const
{
    float camera_work = 0;
    if (player->GetLocation().x >= 350)camera_work = -player->GetLocation().x + 350;
    
    stage->Draw(camera_work);
    player->Draw(camera_work);
    ui->Draw();
}

AbstractScene* GameMain::ChangeScene()
{
    return this;
}