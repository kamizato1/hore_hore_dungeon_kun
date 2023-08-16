#include"DxLib.h"
#include"Title.h"
#include"GameMain.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
Title::Title()
{
    flashing_time = 0;
    push_time = 0;
    can_scene_change = FALSE;
    image = LoadGraph("images/home.png");
    imgae1 = LoadGraph("images/start.png");
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
    push_time++;

    flashing_time++;

    if (flashing_time >= 60)
    {
        flashing_time = 0;
    }

    if (key->KeyDown(B) && push_time >= 30)
    {
        can_scene_change = TRUE;
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

    //カーソル位置
    DrawTriangle(745, 280, 700, 240, 700, 320, GetColor(250, 0, 0), TRUE);
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