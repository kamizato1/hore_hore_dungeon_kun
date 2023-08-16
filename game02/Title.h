#pragma once

#include"AbstractScene.h"
#include"Key.h"
#include"define.h"


class Title : public AbstractScene
{
private:

    //テスト
    int image;
    int imgae1;
    int cursor_image; 
    int cursor_y;
    //テスト

    int flashing_time; //文字点滅時間
    int input_time; // 入力受付時間
    int select_menu; // 選択しているメニュー

    bool can_scene_change; //次のシーンに行けるか

    //連番機能がついた構造体
    enum class MENU
    {
        GAME_START,
        HELP,
        RANKING,
        CLEDIT,
        END,
        MENU_SIZE
    };


public:

    //コンストラクタ
    Title();

    ////デストラクタ
    ~Title();

    //描画以外の更新を実装する
    void Update(Key* key) override;

    //描画に関することを実装する
    void Draw() const override;

    //シーン切り替え
    AbstractScene* ChangeScene() override;

};