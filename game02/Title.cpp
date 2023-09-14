#include"DxLib.h"
#include"Title.h"
#include"StageSelect.h"
#include"Opening.h"
#include"GameMain.h"

#define  INPUT_ACCEPTANCE_TIME 10

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Title::Title()
{
	input_time = 0;
	can_scene_change = FALSE;
	select_menu = 0;
	image = LoadGraph("images/Title.png");
	int menu_image[8];
	LoadDivGraph("images/Menu/menu.png", 8, 2, 4, 600, 100, menu_image);
	bgm = LoadSoundMem("bgm/Title.mp3");
	help = false;
	int count = 0;
	for (int i = 0; i < MENU_NUM; i++)
	{
		for (int j = 0; j < 2; j++)this->menu_image[i][j] = menu_image[count++];
	}
	help_menu = 0;

	credit = false;

	decision_se = LoadSoundMem("bgm/Click.mp3");
	move_se = LoadSoundMem("bgm/MoveCursor.mp3");

	help_image[0] = LoadGraph("images/Menu/help.png");
	help_image[1] = LoadGraph("images/Menu/map (2).png");
	help_image[2] = LoadGraph("images/Menu/map (3).png");

	credit_image = LoadGraph("images/Menu/map.png");

	LoadDivGraph("images/Ui/number.png", 10, 10, 1, 20, 40, num_image);
	LoadDivGraph("images/Ui/sign.png", 2, 2, 1, 20, 40, slash_image);
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Title::~Title()
{

}

//-----------------------------------
// �X�V
//-----------------------------------
void Title::Update(Key* key)
{

	if (CheckSoundMem(bgm) != 1) {   //SE������Ă��Ȃ�������Đ�
		ChangeVolumeSoundMem(255 * 40 / 100, bgm); //SE���ʒ��� 255�ő剹�ʂ���80%�Đ�
		PlaySoundMem(bgm, DX_PLAYTYPE_BACK, TRUE); //SE�Đ�
	}

	//�{�^���������ꂽ��

	if (credit == false && help == false)
	{

		if (key->KeyDown(B) && select_menu == 1)
		{
			help = true;
			ChangeVolumeSoundMem(255 * 40 / 100, decision_se); //SE���ʒ��� 255�ő剹�ʂ���80%�Đ�
			PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE); //SE�Đ�
		}

		else if (key->KeyDown(B) && select_menu == 2)
		{
			credit = true;
			ChangeVolumeSoundMem(255 * 40 / 100, decision_se); //SE���ʒ��� 255�ő剹�ʂ���80%�Đ�
			PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE); //SE�Đ�
		}

		else if (key->KeyDown(B))
		{
			ChangeVolumeSoundMem(255 * 40 / 100, decision_se); //SE���ʒ��� 255�ő剹�ʂ���80%�Đ�
			PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE); //SE�Đ�
			can_scene_change = TRUE;
		}

	}
	if (help)
	{

		if (++input_time > INPUT_ACCEPTANCE_TIME)
		{
			if (key->GetStickAngle(L).x > 0)
			{

				ChangeVolumeSoundMem(255 * 40 / 100, move_se); //SE���ʒ��� 255�ő剹�ʂ���80%�Đ�
				PlaySoundMem(move_se, DX_PLAYTYPE_BACK, TRUE); //SE�Đ�

				if (++help_menu == 3)help_menu = 0;
				input_time = 1;
			}
			else if (key->GetStickAngle(L).x < 0)
			{

				ChangeVolumeSoundMem(255 * 40 / 100, move_se); //SE���ʒ��� 255�ő剹�ʂ���80%�Đ�
				PlaySoundMem(move_se, DX_PLAYTYPE_BACK, TRUE); //SE�Đ�

				if (--help_menu < 0)help_menu = 2;
				input_time = 1;
			}
		}

		if (key->KeyDown(A))
		{
			ChangeVolumeSoundMem(255 * 40 / 100, decision_se); //SE���ʒ��� 255�ő剹�ʂ���80%�Đ�
			PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE); //SE�Đ�
			input_time = 1;
			help_menu = 0;
			help = false;
		}

	}

	else if(credit)
	{

		if (key->KeyDown(A))
		{
			ChangeVolumeSoundMem(255 * 40 / 100, decision_se); //SE���ʒ��� 255�ő剹�ʂ���80%�Đ�
			PlaySoundMem(decision_se, DX_PLAYTYPE_BACK, TRUE); //SE�Đ�
			credit = false;
		}
	}

	else
	{

		//���͎�t��̂�
		if (++input_time > INPUT_ACCEPTANCE_TIME)
		{
			if (key->GetStickAngle(L).y > 0)
			{

				ChangeVolumeSoundMem(255 * 40 / 100, move_se); //SE���ʒ��� 255�ő剹�ʂ���80%�Đ�
				PlaySoundMem(move_se, DX_PLAYTYPE_BACK, TRUE); //SE�Đ�

				if (++select_menu == MENU_NUM)select_menu = 0;
				input_time = 1;
			}
			else if (key->GetStickAngle(L).y < 0)
			{

				ChangeVolumeSoundMem(255 * 40 / 100, move_se); //SE���ʒ��� 255�ő剹�ʂ���80%�Đ�
				PlaySoundMem(move_se, DX_PLAYTYPE_BACK, TRUE); //SE�Đ�

				if (--select_menu < 0)select_menu = MENU_NUM - 1;
				input_time = 1;
			}
		}

	}

}

//-----------------------------------
// �`��
//-----------------------------------
void Title::Draw() const
{
	//�w�i�摜
	DrawGraph(0, 0, image, false);

	for (int i = 0; i < MENU_NUM; i++)
	{
		bool flg = FALSE;
		if (i == select_menu)flg = TRUE;

		DrawRotaGraph(990, 250 + (i * 100), 1, 0, menu_image[i][flg], TRUE);
	}

	if (help)
	{
		DrawRotaGraph(640, 400, 1.15f, 0, help_image[help_menu], TRUE);
		DrawRotaGraph(1000, 100, 1, 0, num_image[help_menu + 1], TRUE);
		DrawRotaGraph(1040, 100, 1, 0, slash_image[1], TRUE);
		DrawRotaGraph(1080, 100, 1, 0, num_image[3], TRUE);
	}

	if (credit)
	{
		DrawRotaGraph(640, 400, 1.15f, 0, credit_image, TRUE);
	}

}

//-----------------------------------
// �J��
//-----------------------------------
AbstractScene* Title::ChangeScene()
{
	//�{�^���������ꂽ��
	if (can_scene_change)
	{
		switch (select_menu)
		{
		case 0: //�Q�[�����C���ɑJ��
			StopSoundMem(bgm);
			return new StageSelect(0);
			break;

		case 3: //�Q�[���I��
			return nullptr;
			break;
		}
	}

	if (help == false && credit == false)
	{
		//���삵�Ȃ������玆�ŋ�
		if (input_time % 600 == 0)
		{
			StopSoundMem(bgm);
			return new Opening();
		}
	}


	return this;
}