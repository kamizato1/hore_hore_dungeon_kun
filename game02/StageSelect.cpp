#include "StageSelect.h"


//�����t����
#define TIME 60

//�X�e�B�b�N�̊��x
#define SENSITIVITY 1000

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
StageSelect::StageSelect()
{
	image = 0;
	stage_number = 0;
	operating_time = 0;

	transition = false;
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
	if (key->GetStickAngle(L).x > 0 || key->GetStickAngle(L).x < 0)
	{
		++operating_time;
	}

	//�����
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
// �`��
//-----------------------------------
void StageSelect::Draw() const
{
	//DrawGraph(0, 0, image, false);
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
