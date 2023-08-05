#include "Result.h"
#include"DxLib.h"

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Result::Result(int block_break, int time, int item_block)
{
	
	image = 0;

	score = 0;

	transition = false;

	//�A�C�e���i�u���b�N�j
	int block = 0;


	//�A�C�e���̃u���b�N�̐���0��������u���b�N�̐����P�ɕύX
	if (item_block == 0)
	{
		block = 1;
	}
	else
	{
		block = item_block;
	}
	
	//�X�R�A�v�Z
	//�c��u���b�N������
	score = block * time;

	//�󂵂��u���b�N�̐�*(������)
	score += 20 * block_break;

//-----------------------------------
// ��̃X�R�A�ɂ��āi�v�l���j
// 
// �J�M 
//-----------------------------------
	
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Result::~Result()
{

}

//-----------------------------------
// �X�V
//-----------------------------------
void Result::Update(Key* key)
{
	if (key->KeyDown(B))
	{
		transition = true;
	}
}

//-----------------------------------
// �`��
//-----------------------------------
void Result::Draw() const
{

	//DrawGraph(0, 0, image, false);

	DrawString(620, 10, "Result", 0xffffff);

	DrawFormatString(640, 310, 0xFFFFFF, "�X�R�A %d", score);

	//�X�R�A���������A���ꂼ��̃X�R�A�̓��_��\��


}

//-----------------------------------
// �J��
//-----------------------------------
AbstractScene* Result::ChangeScene()
{

	if (transition)
	{
		//�e�X�g
		//�^�C�g���ɂ���\��
		return nullptr;
	}

	return this;
}
