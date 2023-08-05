#pragma once
#include "AbstractScene.h"
class Result :
    public AbstractScene
{
private:

    //スコア
    int score;

    //画像
    int image;

    //遷移するのか
    bool transition;

public:

    
    //コンストラクタ
    Result(int block_break,int time ,int item_block);//壊したブロックの数、時間、持っているブロックの数,宝の種類と種類

    //デストラクタ
    ~Result();

    //描画以外の更新を実装する
    void Update(Key* key) override;

    //描画に関することを実装する
    void Draw() const override;

    //シーン切り替え
    AbstractScene* ChangeScene() override;

};

