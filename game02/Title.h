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
    //テスト

    int flashing_time; //文字点滅時間
    int push_time; // ゲームメインに行けるようになるまでの時間
    bool can_scene_change; //次のシーンに行けるか


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