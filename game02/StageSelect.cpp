#include"DxLib.h"
#include "StageSelect.h"

//�����t����
#define TIME 30

//�X�e�B�b�N�̊��x
#define SENSITIVITY 1000

//-----------------------------------
// �R���X�g���N�^
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
// �f�X�g���N�^
//-----------------------------------
StageSelect::~StageSelect()
{

}

//-----------------------------------
// �X�V
//-----------------------------------
void StageSelect::Update(Key* key)
{
	//�X�e�B�b�N�𓮂�������
	if (key->GetStickAngle(L).x == 0)operating_time = TIME;
	else operating_time++;

	//�����
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
// �`��
//-----------------------------------
void StageSelect::Draw() const
{
	DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1, 0, image, TRUE);
	DrawFormatString(0, 0, 0xffffff, "%d", stage_number);
}

//-----------------------------------
// �J��
//-----------------------------------
AbstractScene* StageSelect::ChangeScene()
{
	//���̉�ʂɑJ�ڂ���̂�
	if (transition)
	{
		return this; //�R���X�g���N�^�Ŏw�肷��\��
	}

	return this;
}
