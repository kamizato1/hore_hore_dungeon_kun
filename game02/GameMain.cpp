#include"DxLib.h"
#include"GameMain.h"
#include"Title.h"
#include"Stage.h"
#include"StageSelect.h"
#include"Result.h"
#include"GameOver.h"

#define TIME 160
#define MAX_SWAY_WIDTH 5
#define SWAY_SIZE 0.5

GameMain::GameMain(int stage_num)
{
    int stage_width[STAGE_NUM];
    FILE* fp_w;//スコアファイル読み込み
    fopen_s(&fp_w, "data/stagewidth.txt", "r");
    for (int i = 0; i < STAGE_NUM; i++)fscanf_s(fp_w, "%d", &stage_width[i]);
    fclose(fp_w);

    stage_bgm = LoadSoundMem("bgm/GameMain.mp3");
    stage_clear_bgm = LoadSoundMem("bgm/GameClearSe.mp3");
    earthquake_se = LoadSoundMem("bgm/earthquake.mp3");

    stage = new Stage(stage_num, stage_width[stage_num]);
    player = new Player();
    ui = new Ui();
    pause = new class Pause();
    this->stage_num = stage_num;
    life = 3;
    max_scroll = stage_width[stage_num] - 4;
    change_result_scene = FALSE;
    change_game_over_scene = FALSE;
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
    Pause(TRUE);
    StopSoundMem(stage_bgm);
    PlaySoundMem(stage_bgm, DX_PLAYTYPE_LOOP, TRUE);
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
        if (player->GetClear())
        {
            if (clear == FALSE)
            {
                Pause(TRUE);
                PlaySoundMem(stage_clear_bgm, DX_PLAYTYPE_BACK, TRUE);
                StopSoundMem(stage_bgm);
            }
            clear = TRUE;   
        }
        else
        {
            if (player->GetPlayerDie())die = TRUE;
            if (remaining_time == 0)die = TRUE, stage->DeleteFlag();
        }
    }
    
    if ((key->KeyDown(START)) && (!die) && (!clear))
    {
        stop = !stop;
        if (stop)
        {
            Pause(TRUE);
            pause->Init();
        }
        else Pause(FALSE);
    }

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
                if (!sway_flg)
                {
                    sway_flg = TRUE;
                    PlaySoundMem(earthquake_se, DX_PLAYTYPE_BACK, TRUE);
                }
            }
        }
        change_result_scene = ui->Update(clear);
    }
    else if (pause->Update(key))stop = !stop;
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
   
    ui->Draw(remaining_time, life,stage->GetPickaxeFlg(), player->GetPlayerUi());

    SetDrawBright(255, 255, 255);

    if (stop) pause->Draw();
}

void GameMain::ReStart()
{
    if (--life == 0)
    {
        StopSoundMem(stage_bgm);
        change_game_over_scene = TRUE;
    }
    else
    {
        Init();
        player->Init();
        stage->Init();
    }
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
        if (pause->GetChangeScene() == 1)
        {
            StopSoundMem(stage_bgm);
            Pause(TRUE);
            return new GameMain(stage_num);
        }
        else if (pause->GetChangeScene() == 2)
        {
            StopSoundMem(stage_bgm);
            Pause(TRUE);
            return new StageSelect(stage_num);
        }
    }
    else if (change_result_scene)
    {
        Pause(TRUE);
        return new Result(stage_num, player->GetTreasureNum());
    }

    if (change_game_over_scene)
    {
        Pause(TRUE);
        return new GameOver(stage_num);
    }

    return this;
}

void GameMain::Pause(bool flg)
{
    if (flg)
    {
        StopSoundMem(earthquake_se);
    }
    else
    {
        if(sway_flg)PlaySoundMem(earthquake_se, DX_PLAYTYPE_BACK, FALSE);
    }

    stage->Pause(flg);
}