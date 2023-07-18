#pragma once
#include "define.h"

struct KEY
{
	bool flg;
};

struct STICK_ANGLE
{
	int x, y;
};

class Key //キーの更新処理
{
private:

	int a;

	KEY now_key[KEY_NUM];
	KEY old_key[KEY_NUM];

	STICK_ANGLE l_stick_angle;
	STICK_ANGLE r_stick_angle;

public:

	Key();//コンストラクタ

	void Update();
	bool KeyPressed(int key_type);//押してるとき
	bool KeyUp(int key_type);//離したとき
	bool KeyDown(int key_type);//押した瞬間

	DATA GetStickAngle(int key);
};