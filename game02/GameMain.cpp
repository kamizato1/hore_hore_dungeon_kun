#include"DxLib.h"
#include"GameMain.h"
#include"Title.h"
#include"Stage.h"

#define TIME 200
#define MAX_SWAY_WIDTH 5
#define SWAY_SIZE 0.5

GameMain::GameMain()
{
    stage = new Stage();
    player = new Player();
    ui = new Ui();
    pause = new Pause();
    life = 3;
    Init();
}

GameMain::~GameMain()
{
    delete player;
    delete stage;
    delete ui;
    delete pause; 
}

void GameMain::Init()
{
    die = FALSE;
    stop = FALSE;
    clear = FALSE;
    time = 0;
    remaining_time = TIME - (time / FPS);
    sway_width = 0;
    max_sway_width = MAX_SWAY_WIDTH;
    sway_size = SWAY_SIZE;
    sway_flg = FALSE;
    screen_brightness = 255;
}

void GameMain::Update(Key* key)
{
    if ((player->GetPlayerDie()) || (remaining_time == 0))
    {
        die = TRUE;
        if (--screen_brightness < 0)
        {
            screen_brightness = 0;
            ReStart();
        }
    }

    if (!clear)
    {
        bool flg = stage->HitFlag(player);
        clear = flg;
        player->SetClear(flg);
    }

    if ((key->KeyDown(START)) && (!die) && (!clear))stop = !stop;

    if (!stop)
    {
        stage->Update();
        player->Update(key, stage);

        if (!clear)
        {
            if (!die)time++;
            remaining_time = TIME - (time / FPS);

            Sway();

            if ((remaining_time == 150) || (remaining_time == 100) || (remaining_time == 50) || (remaining_time == 0))
            {
                if (!sway_flg)sway_flg = TRUE;
            }
        }
    }
    else
    {
        pause->Update(key);
    }
}

void GameMain::Draw() const
{
    float camera_work = 0;
    if (player->GetLocation().x >= 350)camera_work = -player->GetLocation().x + 350;
    if (camera_work <= -(BLOCK_SIZE_X * 100) + SCREEN_WIDTH)camera_work = -(BLOCK_SIZE_X * 100) + SCREEN_WIDTH;
    camera_work += sway_width;

    if (die)SetDrawBright(screen_brightness, screen_brightness, screen_brightness);

    stage->Draw1(camera_work);
    player->Draw(camera_work);
    stage->Draw2(camera_work);
   
    ui->Draw(remaining_time, life);

    SetDrawBright(255, 255, 255);

    if (stop) pause->Draw();
}

void GameMain::ReStart()
{
    life--;
    Init();
    player->Init();
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
        stage->Sway();
    }
}

AbstractScene* GameMain::ChangeScene()
{
    if (stop)
    {
        if (pause->GetNextScene())
        {
            switch (pause->GetSelectMenu())
            {
            case 0:
                stop = false;
                pause->SetNextScene();
                break;
            case 1:
                return new Title();
                break;
            case 2:
                return nullptr;
            default:
                break;
            }
       }
    }

    return this;
}

