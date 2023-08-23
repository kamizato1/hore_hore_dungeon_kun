#include"DxLib.h"
#include"GameMain.h"
#include"Stage.h"

#define TIME 100
#define MAX_SWAY_WIDTH 5
#define SWAY_SIZE 0.5

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
    remaining_time = TIME - (time / FPS);
    falling_block_image = LoadGraph("images/fallingblock.png");
    sway_width = 0;
    max_sway_width = MAX_SWAY_WIDTH;
    sway_size = SWAY_SIZE;
    sway_flg = FALSE;
    screen_brightness = 255;
}

GameMain::~GameMain()
{
    delete player;
    delete stage;
    delete ui;
    fallingblock.clear();
}

void GameMain::Update(Key* key)
{
    if (key->KeyDown(START))stop = !stop;

    if (!stop)
    {
        if(!die)time++;
        remaining_time = TIME - (time / FPS);
        stage->Update();
        player->Update(key, stage);

        Sway();

        for (int i = 0; i < fallingblock.size(); i++)
        {
            fallingblock[i].Update();
            if (fallingblock[i].CanDelete())fallingblock.erase(fallingblock.begin() + i);
        }

        if ((remaining_time == 80) || (remaining_time == 50))
        {
            if (!sway_flg)sway_flg = TRUE;
        }
    }

    if (remaining_time < 0)time = 0;

    if (player->GetPlayerDie()) 
    {
        die = TRUE;
        if (--screen_brightness < 0)screen_brightness = 0;;
    }
}

void GameMain::Draw() const
{
    float camera_work = 0;
    if (player->GetLocation().x >= 350)camera_work = -player->GetLocation().x + 350;
    camera_work += sway_width;

    if (die)SetDrawBright(screen_brightness, screen_brightness, screen_brightness);

    //SetDrawBright(150, 150, 150);
    DrawGraph((camera_work / 10), 0, back_ground_image[2], TRUE);
    DrawGraph((camera_work / 7), 0, back_ground_image[1], TRUE);
    for (int i = 0; i < fallingblock.size(); i++)
    {
        if (fallingblock[i].GetSize() < 0.7)fallingblock[i].Draw(camera_work);
    }
    DrawGraph((camera_work / 5), 0, back_ground_image[0], TRUE);
    

    stage->Draw1(camera_work);
    player->Draw(camera_work);
    stage->Draw2(camera_work);
    for (int i = 0; i < fallingblock.size(); i++)
    {
        if (fallingblock[i].GetSize() >= 0.7)fallingblock[i].Draw(camera_work);
    }

    ui->Draw(remaining_time);

    SetDrawBright(255, 255, 255);

    
    int num = fallingblock.size();
    DrawFormatString(0, 100, 0xffffff, "%d", num);
}

void GameMain::Sway()
{
    if (sway_flg)
    {
        sway_width += sway_size;

        if (((sway_width >  max_sway_width) && (sway_size > 0)) ||
            ((sway_width < -max_sway_width) && (sway_size < 0)))
        {
            sway_size = -sway_size;

            if ((max_sway_width -= 0.1) < 0)
            {
                sway_flg = FALSE;
                max_sway_width = MAX_SWAY_WIDTH;
                sway_size = SWAY_SIZE;
                sway_width = 0;
            }
        }
        
        if (GetRand(10) == 0)
        {
            DATA location;
            location.x = GetRand(SCREEN_WIDTH);
            location.y = -GetRand(50);
            float speed = GetRand(15) + 1;
            fallingblock.emplace_back(location, falling_block_image, speed, (speed / 10));
        }

        stage->Sway();
    }
}

AbstractScene* GameMain::ChangeScene()
{
    return this;
}

