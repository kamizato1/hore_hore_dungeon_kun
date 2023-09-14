#pragma once
#include "AbstractScene.h"

//ステージセレクト画面について（３ステージ）
//New スーパーマリオブラザーズのステージ選択画面を参考にする。

class StageSelect : public AbstractScene
{
private:

    int stage_number;//現在選択中のステージ番号
    int stage_score[STAGE_NUM];
    int number_image[10];
    int operating_time;//操作受付
    int back_ground_image[5];//背景画像
    int player_image[5]; //プレイヤー画像
    int player_image_type; //画像イメージ
    int player_image_change_time;
    int clear_stage; //クリアステージ
    DATA player_location[STAGE_NUM];
    bool transition;//次の画面に遷移するのか
 
public:

    
    StageSelect(int stage_num);//コンストラクタ
    ~StageSelect();//デストラクタ

    void Update(Key* key) override;//描画以外の更新を実装する
    void Draw() const override;//描画に関することを実装する

    AbstractScene* ChangeScene() override; //シーン切り替え
};

