#include "StageSelect.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
StageSelect::StageSelect()
{
	stage_number = 0;
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

}

//-----------------------------------
// �`��
//-----------------------------------
void StageSelect::Draw() const
{

}

//-----------------------------------
// �J��
//-----------------------------------
AbstractScene* StageSelect::ChangeScene()
{
	//���̉�ʂɑJ�ڂ���̂�
	if (transition)
	{
		//�X�e�[�W�̍��ɂ���ĕύX
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
