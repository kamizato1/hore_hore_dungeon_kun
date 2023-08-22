#pragma once

#include"AbstractScene.h"
#include"Key.h"
#include"define.h"

class Title : public AbstractScene
{
private:

    int image; //背景画像
    int cursor_image;  //カーソル画像
    int cursor_y;   //カーソル位置
    int input_time; //入力受付時間
    int select_menu; // 現在入力しているメニュー
    bool can_scene_change; //次のシーンに行けるか
    

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