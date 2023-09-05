#pragma once
#include "AbstractScene.h"

//ステージセレクト画面について（３ステージ）
//New スーパーマリオブラザーズのステージ選択画面を参考にする。

class StageSelect : public AbstractScene
{
private:

    int stage_number;//現在選択中のステージ番号
    int stage_score[STAGE_NUM];
    int stage_width[STAGE_NUM];
    int number_image[10];

    int operating_time;//操作受付

    int back_ground_image;//背景画像
    int player_image[4]; //プレイヤー画像
    int type_image; //画像イメージ

    //カーソルの座標
    float cursor_x;
    float cursor_y;

    float player_x;
    float player_y;

    

    //次の画面に遷移するのか
    bool transition;

    //向いている方向
    bool direction;

public:

    //コンストラクタ
    StageSelect(int stage_num);

    //デストラクタ
    ~StageSelect();

    //描画以外の更新を実装する
    void Update(Key* key) override;

    //描画に関することを実装する
    void Draw() const override;

    //シーン切り替え
    AbstractScene* ChangeScene() override;

};

