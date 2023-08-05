#include "Result.h"
#include"DxLib.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
Result::Result(int block_break, int time, int item_block)
{
	
	image = 0;

	score = 0;

	transition = false;

	//アイテム（ブロック）
	int block = 0;


	//アイテムのブロックの数が0だったらブロックの数を１に変更
	if (item_block == 0)
	{
		block = 1;
	}
	else
	{
		block = item_block;
	}
	
	//スコア計算
	//残りブロック＊時間
	score = block * time;

	//壊したブロックの数*(調整中)
	score += 20 * block_break;

//-----------------------------------
// 宝のスコアについて（思考中）
// 
// カギ 
//-----------------------------------
	
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Result::~Result()
{

}

//-----------------------------------
// 更新
//-----------------------------------
void Result::Update(Key* key)
{
	if (key->KeyDown(B))
	{
		transition = true;
	}
}

//-----------------------------------
// 描画
//-----------------------------------
void Result::Draw() const
{

	//DrawGraph(0, 0, image, false);

	DrawString(620, 10, "Result", 0xffffff);

	DrawFormatString(640, 310, 0xFFFFFF, "スコア %d", score);

	//スコア正式決定後、それぞれのスコアの得点を表示


}

//-----------------------------------
// 遷移
//-----------------------------------
AbstractScene* Result::ChangeScene()
{

	if (transition)
	{
		//テスト
		//タイトルにする予定
		return nullptr;
	}

	return this;
}
