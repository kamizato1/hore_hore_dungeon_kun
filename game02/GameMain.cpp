#include"DxLib.h"
#include"GameMain.h"
#include"Title.h"
#include"Stage.h"
#include"Result.h"

#define TIME 55
#define MAX_SWAY_WIDTH 5
#define SWAY_SIZE 0.5

GameMain::GameMain(int stage_num)
{
    int stage_width[STAGE_NUM];
    FILE* fp_w;//スコアファイル読み込み
    fopen_s(&fp_w, "data/stagewidth.txt", "r");
    for (int i = 0; i < STAGE_NUM; i++)fscanf_s(fp_w, "%d", &stage_width[i]);
    fclose(fp_w);

    stage = new Stage(stage_num, stage_width[stage_num]);
    player = new Player();
    ui = new Ui();
    pause = new Pause();
    this->stage_num = stage_num;
    life = 3;
    max_scroll = stage_width[stage_num] - 4;
    change_scene = FALSE;
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
    if (die)
    {
        if (--screen_brightness < 0)
        {
            screen_brightness = 0;
            ReStart();
        }
    }
    else
    {
        if (player->GetClear())clear = TRUE;
        else
        {
            if (player->GetPlayerDie())die = TRUE;
            if (remaining_time == 0)die = TRUE, stage->DeleteFlag();
        }
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
        
        change_scene = ui->Update(clear);

    }
    else pause->Update(key);
}

void GameMain::Draw() const
{
    float camera_work = 0.0f;
    if (player->GetLocation().x >= 350.0f)camera_work = -player->GetLocation().x + 350.0f;
    if (camera_work <= -(BLOCK_SIZE_X * max_scroll) + SCREEN_WIDTH)camera_work = -(BLOCK_SIZE_X * max_scroll) + SCREEN_WIDTH;
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
    stage->Init();
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

    if(change_scene)return new Result(stage_num, player->GetTreasureNum());

    return this;
}

