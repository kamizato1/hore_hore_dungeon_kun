#include "StageSelect.h"


//操作受付時間
#define TIME 60

//スティックの感度
#define SENSITIVITY 1000

//-----------------------------------
// コンストラクタ
//-----------------------------------
StageSelect::StageSelect()
{
	image = 0;
	stage_number = 0;
	operating_time = 0;

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
	//スティックを動かしたら
	if (key->GetStickAngle(L).x > 0 || key->GetStickAngle(L).x < 0)
	{
		++operating_time;
	}

	//操作受け
	if (operating_time > TIME)
	{
		if (key->GetStickAngle(L).x > SENSITIVITY)
		{

			if (++stage_number > 3)
			{
				stage_number = 0;
			}

			operating_time = 0;
		}
		else if(key->GetStickAngle(L).x < -SENSITIVITY)
		{
			if (--stage_number < 0)
			{
				stage_number = 3;
			}

			operating_time = 0;
		}
	}
}

//-----------------------------------
// 描画
//-----------------------------------
void StageSelect::Draw() const
{
	//DrawGraph(0, 0, image, false);
}

//-----------------------------------
// 遷移
//-----------------------------------
AbstractScene* StageSelect::ChangeScene()
{
	//次の画面に遷移するのか
	if (transition)
	{
		return this; //コンストラクタで指定する予定
	}

	return this;
}
