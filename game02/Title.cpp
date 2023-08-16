#include"DxLib.h"
#include"Title.h"
#include"GameMain.h"

#define INPUT_ACCEPTANCE_TIME 60

//-----------------------------------
// コンストラクタ
//-----------------------------------
Title::Title()
{
    flashing_time = 0;
    input_time = 0;
    cursor_y = 0;

    can_scene_change = FALSE;

    select_menu = static_cast<int>(MENU::GAME_START); 
    
    image = LoadGraph("images/home.png");
    imgae1 = LoadGraph("images/start.png");
    cursor_image = LoadGraph("images/triangle.png");
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Title::~Title()
{

}


//-----------------------------------
// 更新
//-----------------------------------
void Title::Update(Key* key)
{
    input_time++;

    flashing_time++;

    if (flashing_time >= 60)
    {
        flashing_time = 0;
    }

    if (key->KeyDown(B))
    {
        can_scene_change = TRUE;
    }

    //超高速でカーソルが移動しないようにする
    if (++input_time > INPUT_ACCEPTANCE_TIME)
    {
        if (key->GetStickAngle(L).y > 0)
        {
            select_menu = (select_menu - 1 + static_cast<int>(MENU::MENU_SIZE)) % static_cast<int>(MENU::MENU_SIZE);
        }
        else if (key->GetStickAngle(L).y < 0)
        {
            select_menu = (select_menu + 1) % static_cast<int>(MENU::MENU_SIZE);
        }
    }
}


//-----------------------------------
// 描画
//-----------------------------------
void Title::Draw() const
{
    SetFontSize(30);

    DrawString(190, 200, "惚れ掘れダンジョン君！", 0xffffff);
    
    if (flashing_time / 30 == 0)
    {
        DrawString(190, 300, "Bボタンを押そう！", 0xffffff);
    }


    DrawGraph(0, 0, image, false);
    DrawGraph(715, 250, imgae1, true);

    DrawFormatString(100, 100, 0xFFFFFF, "%d ", select_menu);

   // //カーソル位置
    //DrawTriangle(745, 280, 700, 240, 700, 320, GetColor(250, 0, 0), TRUE);
}


//-----------------------------------
// 遷移
//-----------------------------------
AbstractScene* Title::ChangeScene()
{

    if (can_scene_change)
    {
        return new GameMain(); //次の遷移
    }

    return this;
}