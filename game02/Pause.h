#pragma once
#include"Key.h"

class Pause
{
private:

    //メニュ一覧
    enum class MENU
    {
        GAME_START,
        TITLE,
        END,
        MENU_SIZE
    };

    int cursor_image;  //カーソル画像
    int cursor_y;   //カーソル位置
    int input_time; //入力受付時間
    int select_menu; // 現在入力しているメニュー

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

    //値参照
    int GetSelectMenu();
   
    //値参照
    bool GetNextScene();

};

