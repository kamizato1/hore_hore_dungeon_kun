#pragma once
#include"Key.h"

class Pause
{
private:

    int select_se;
    int decision_se;
    int return_se;

    int input_time; //入力受付時間
    int select_menu_num; // 現在入力しているメニュー
    bool select_menu_decision;
    int answer_num;
    bool answer_decision;

    int menu_image[4][2]; //画像
    int answer_image[2][2]; //最終確認画像
    int text_image[3];
    int help_image[3];
    int number_image[4];
    int back_ground_image; //背景黒
    int pause_image;

    int set_menu_image[8]; //画像
    int set_answer_image[4]; //最終確認画像

    int help_num;
    int change_scene;
    bool can_close;

public:

    
    Pause();//コンストラクタ
    void Delete();

    bool Update(Key* key);//描画以外の更新を実装する
    void Draw() const;//描画に関することを実装する
    
    void MenuUpdate(Key* key);
    void TextUpdate(Key* key);

    void Init();

    int GetChangeScene() { return change_scene; }

};

