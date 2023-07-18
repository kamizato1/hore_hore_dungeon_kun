#include"DxLib.h"
#include"Title.h"
#include"GameMain.h"


Title::Title()
{
    flashing_time = 0;
    push_time = 0;
    can_scene_change = FALSE;
}

void Title::Update(Key* key)
{
    push_time++;
    flashing_time++;
    if (flashing_time >= 60)flashing_time = 0;
    if (key->KeyDown(B) && push_time >= 30)can_scene_change = TRUE;
}

void Title::Draw() const
{
    SetFontSize(30);
    if (flashing_time / 30 == 0)DrawString(190, 300, "Bボタンを押そう！", 0xffffff);
}

AbstractScene* Title::ChangeScene()
{
    if (can_scene_change)return new GameMain(); //bボタンを押したらゲームメインに行く

    return this;
}