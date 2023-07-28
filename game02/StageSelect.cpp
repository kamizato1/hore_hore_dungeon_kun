#include "StageSelect.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
StageSelect::StageSelect()
{
	stage_number = 0;
	transition = false;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
StageSelect::~StageSelect()
{

}

//-----------------------------------
// 更新
//-----------------------------------
void StageSelect::Update(Key* key)
{

}

//-----------------------------------
// 描画
//-----------------------------------
void StageSelect::Draw() const
{

}

//-----------------------------------
// 遷移
//-----------------------------------
AbstractScene* StageSelect::ChangeScene()
{
	//次の画面に遷移するのか
	if (transition)
	{
		//ステージの作りによって変更
		switch (stage_number)
		{

		case 0:
			return this;
			break;
		case 1:
			return this;
			break;
		case 2:
			return this;
			break;
		}
	}

	return this;
}
