#pragma once
#include"Key.h"

class Pause
{
private:

    //メニュ一覧
    enum class MENU
    {
        TITLE,
        STAGE_SELECT,
        HELP,
        END,
        MENU_SIZE
    };

    //最終決定
    enum class SELECTION
    {
        YES,
        NO,
        MENU_SIZE
    };

    int cursor_image;  //カーソル画像
    int cursor_y;   //カーソル位置
    int cursor_x;  //カーソル位置
    int input_time; //入力受付時間
    int select_menu; // 現在入力しているメニュー
    int confirmation_menu; //現在入力しているメニュー

    int image[11]; //画像
    int image1[5]; //最終確認画像
    int background; //背景黒


    bool confirmation; //確認画面

    bool next_scene; //次のシーン

public:

    //コンストラクタ
    Pause();

    //デストラクタ
    ~Pause();

    //描画以外の更新を実装する
    void Update(Key* key);

    //描画に関することを実装する
    void Draw() const;
    
    //値変更
    void SetNextScene();
    void Setconfirmation();

    //値参照
    int GetSelectMenu();
   
    //値参照
    bool GetNextScene();

};

