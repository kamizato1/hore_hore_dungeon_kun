#pragma once

#include"AbstractScene.h"
#include"Key.h"
#include"define.h"

#define MENU_NUM 4

class Title : public AbstractScene
{
private:

    int image; //背景画像
    int help_image[3]; //ヘルプイメージ
    int credit_image; //クレジット画面
    int menu_image[MENU_NUM][2]; //メニュー画像
    int num_image[4];
    int slash_image;
    int set_menu_image[8];

    int bgm; //BGM
    int move_se; //動くときのSE
    int return_se;
    int decision_se; //決定オン

    int input_time; //入力受付時間
    int select_menu; // 現在入力しているメニュー
    int help_menu; //ヘルプメニュ


    bool can_scene_change; //次のシーンに行けるか
    bool help; //ヘルプ画面開くのか
    bool credit; //クレジット

public:

    //コンストラクタ
    Title();

    ////デストラクタ
    ~Title();

    //描画以外の更新を実装する
    void Update(Key* key) override;

    //描画に関することを実装する
    void Draw() const override;
    void Delete() override;
    //シーン切り替え
    AbstractScene* ChangeScene() override;

};