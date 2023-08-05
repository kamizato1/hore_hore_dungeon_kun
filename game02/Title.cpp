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