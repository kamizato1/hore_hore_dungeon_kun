#include"DxLib.h"
#include "StageSelect.h"

//操作受付時間
#define TIME 30

//スティックの感度
#define SENSITIVITY 1000

//-----------------------------------
// コンストラクタ
//-----------------------------------
StageSelect::StageSelect()
{
	image = LoadGraph("images/stageselect.png");
	stage_number = 0;
	operating_time = 0;
	transition = false;
	cursor_x = 0;
	cursor_y = 0;

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
	if (key->GetStickAngle(L).x == 0)operating_time = TIME;
	else operating_time++;

	//操作受け
	if (operating_time >= TIME)
	{
		if (key->GetStickAngle(L).x > 0)
		{
			if (++stage_number > 3)stage_number = 0;
			operating_time = 0;
		}
		else if(key->GetStickAngle(L).x < 0)
		{
			if (--stage_number < 0)stage_number = 3;
			operating_time = 0;
		}
	}
}

//-----------------------------------
// 描画
//-----------------------------------
void StageSelect::Draw() const
{
	DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1, 0, image, TRUE);
	DrawFormatString(0, 0, 0xffffff, "%d", stage_number);
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
