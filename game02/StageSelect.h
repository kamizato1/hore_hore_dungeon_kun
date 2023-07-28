#pragma once
#include "AbstractScene.h"


//ステージセレクト画面について（３ステージ）
//New スーパーマリオブラザーズのステージ選択画面を参考にする。



class StageSelect :
    public AbstractScene
{
private:

    //現在選択中のステージ番号
    int stage_number;

    

    //次の画面に遷移するのか
    bool transition;

public:

    //コンストラクタ
    StageSelect();

    //デストラクタ
    ~StageSelect();

    //描画以外の更新を実装する
    void Update(Key* key) override;

    //描画に関することを実装する
    void Draw() const override;

    //シーン切り替え
    AbstractScene* ChangeScene() override;

};

