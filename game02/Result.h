#pragma once
#include "AbstractScene.h"
#include "define.h"

class Result :
    public AbstractScene
{
private:

    int score; //スコア

    TREASURE_TYPE treasure; //所持していたアイテムを保存する。

    int time; //残り時間を格納する。

    int block_break; //破壊したブロックの数

    int block; //所持していたブロックの数（お助けアイテム）

public:

    
    //コンストラクタ
    Result(int block_break,int time, int block, TREASURE_TYPE treasure);//壊したブロックの数、時間、持っているブロックの数,宝の種類と種類

    //デストラクタ
    ~Result();

    //描画以外の更新を実装する
    void Update(Key* key) override;

    //描画に関することを実装する
    void Draw() const override;

    //シーン切り替え
    AbstractScene* ChangeScene() override;

};

