#pragma once
#include "AbstractScene.h"
class Opening :
    public AbstractScene
{
private:

    //アニメーション
    int animation;

    //アニメーション時間
    int animation_time;

    //表示時間
    int display_time;

    //画像   
    int image[5];

    //次のシーンに行けるのか
    bool can_scene_change;

public:

    //コンストラクタ
    Opening();

    ////デストラクタ
    ~Opening();

    //描画以外の更新を実装する
    void Update(Key* key) override;

    //描画に関することを実装する
    void Draw() const override;

    //シーン切り替え
    AbstractScene* ChangeScene() override;

};

