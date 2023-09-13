#include "Opening.h"
#include "DxLib.h"
#include"Title.h"

Opening::Opening()
{
	//紙芝居画像
	image[0] = LoadGraph("images/Opening/紙芝居2.png");
	image[1] = LoadGraph("images/Opening/紙芝居3.png");
	image[2] = LoadGraph("images/Opening/紙芝居4.png");
	image[3] = LoadGraph("images/Opening/紙芝居5.png");
	image[4] = LoadGraph("images/Opening/紙芝居6.png");

	//文字用画像
	character_image[0] = LoadGraph("images/Opening/Character/とある一軒家。.png");
	character_image[1] = LoadGraph("images/Opening/Character/その少年は家のそうじをしていました。.png");
	character_image[2] = LoadGraph("images/Opening/Character/するとたなの中から古い紙を見つけました。.png");
	character_image[3] = LoadGraph("images/Opening/Character/「これは、トレジャーハンターだった.png");
	character_image[4] = LoadGraph("images/Opening/Character/少年はタカラをさがす旅に出ましたとさ。.png");

	//背景
	background_image = LoadGraph("images/Opening/map.png");

	bgm = LoadSoundMem("bgm/Opnig.mp3");

	size = 0;
	animation = 0;
	animation_time = 0;
	display_time = 0;
	time = 0;
	brightness = 0;
	story_no = 0;

	can_scene_change = false;

}

Opening::~Opening()
{

}

void Opening::Update(Key* key)
{

	int old_story_no = story_no;


	if (CheckSoundMem(bgm) != 1) {   //SEが流れていなかったら再生
		ChangeVolumeSoundMem(255 * 40 / 100, bgm); //SE音量調整 255最大音量から80%再生
		PlaySoundMem(bgm, DX_PLAYTYPE_BACK, TRUE); //SE再生
	}

	//Aキーが押された、もしくは紙芝居終了時にタイトルへ
	if (key->KeyDown(B) || story_no > 4)
	{
		can_scene_change = true;
	}

	//60で÷と秒に治る
	if (++time % 400 == 0) 
	{
		++story_no;
	}

	if (brightness< 255)
	{
		brightness += 1;
	}


	if (story_no != old_story_no)
	{
		brightness = 0;
	}

}

void Opening::Draw() const
{
	
	//https://scrapbox.io/dxlib/SetDrawBlendMode
	DrawRotaGraph(640, 360, 1, 0, background_image, false);
	
	//透明度
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, brightness);

	DrawRotaGraph(640, 300,0.7f,0 ,image[story_no], false);

	DrawRotaGraph(640, 630, 0.5, 0, character_image[story_no], true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

}

AbstractScene* Opening::ChangeScene()
{
	//シーン切り替え
	if (can_scene_change)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		StopSoundMem(bgm);
		return new Title();
	}

	return this;
}
