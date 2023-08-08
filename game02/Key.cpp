#include"DxLib.h"
#include "Key.h"

Key::Key()
{
	for (int i = 0; i < KEY_NUM; i++)
	{
		now_key[i].flg = false;
		old_key[i].flg = false;
	}

	l_stick_angle = { 0,0 };
}

void Key::Update()
{
	for (int i = 0; i < KEY_NUM; i++)
	{
		old_key[i].flg = now_key[i].flg;
		now_key[i].flg = FALSE;
	}

	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A))now_key[A].flg = TRUE;//Aボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)) now_key[B].flg = TRUE;//Bボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6)) now_key[R].flg = TRUE;//Rボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5)) now_key[L].flg = TRUE;//Lボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP))now_key[UP].flg = TRUE;//UPボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN))now_key[DOWN].flg = TRUE;//DOWNボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT))now_key[RIGHT].flg = TRUE;//RIGHTボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT))now_key[LEFT].flg = TRUE;//LEFTボタンが押されているか
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8)) now_key[START].flg = TRUE;//スタートボタンが押されているか


	GetJoypadAnalogInputRight(&r_stick_angle.x, &r_stick_angle.y, DX_INPUT_PAD1); // 入力状態を取得
	GetJoypadAnalogInput(&l_stick_angle.x, &l_stick_angle.y, DX_INPUT_PAD1); // 入力状態を取得

	/*if (l_stick_angle.y < 0)now_key[UP].flg = TRUE; else now_key[UP].flg = FALSE;
	if (l_stick_angle.y > 0)now_key[DOWN].flg = TRUE; else now_key[DOWN].flg = FALSE;
	if (l_stick_angle.x < 0)now_key[LEFT].flg = TRUE; else now_key[LEFT].flg = FALSE;
	if (l_stick_angle.x > 0)now_key[RIGHT].flg = TRUE; else now_key[RIGHT].flg = FALSE;*/
}

bool Key::KeyPressed(int key_type)//押してるとき
{
	if (now_key[key_type].flg)return TRUE;
	else return FALSE;
}

bool Key::KeyUp(int key_type)//離したとき
{
	if ((!now_key[key_type].flg) && (old_key[key_type].flg))return TRUE;
	else return FALSE;
}

bool Key::KeyDown(int key_type)//押した瞬間
{
	if ((!old_key[key_type].flg) && (now_key[key_type].flg))return TRUE;
	else return FALSE;
}

DATA Key::GetStickAngle(int key)
{
	DATA sa = { 0,0 };

	if (key == L)
	{
		sa.x = l_stick_angle.x;
		sa.y = l_stick_angle.y;
	}
	else if (key == R)
	{
		sa.x = r_stick_angle.x;
		sa.y = r_stick_angle.y;
	}

	return sa;
}

void Key::Draw()
{
	DrawFormatString(0, 55, 0xffffff, "x = %d", r_stick_angle.x);
	DrawFormatString(0, 80, 0xffffff, "y = %d", r_stick_angle.y);
}