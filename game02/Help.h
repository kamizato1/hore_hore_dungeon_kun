#pragma once
#include "AbstractScene.h"
class Help :
    public AbstractScene
{
private:

    int image; //画像
    int flashing_time; //文字描画時間

    bool chane_title; //タイトルに遷移するのか

public:
    
    //コンストラクタ
    Help();
    
    //描画以外の更新を実装する
    void Update(Key* key) override;

    //描画に関することを実装する
    void Draw() const override;

    //シーン切り替え
    AbstractScene* ChangeScene() override;

};

