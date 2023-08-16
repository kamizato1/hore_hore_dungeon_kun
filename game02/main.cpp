/********************************************************************
//���C��
********************************************************************/
#include "DxLib.h"

#include"Key.h"
#include"Title.h"
#include"GameMain.h"
#include"SceneManager.h"
#include"define.h"

//�e�X�g(�f�o�b�N)
#include"Result.h"
#include"Help.h"


/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    double dNextTime = GetNowCount();

    // �^�C�g���� test �ɕύX
    SetMainWindowText("����@��_���W�����N");

    ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

    SetAlwaysRunFlag(true);

    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

    if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

    
    SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

    SetFontSize(20);		// �����T�C�Y��ݒ�

    SceneManager* sceneMng = new SceneManager(new GameMain());
    Key* key = new Key();

    while ((ProcessMessage() == 0) && (sceneMng->GetNowScene() != nullptr))
    {
        sceneMng->Update(key);
        key->Update();
        sceneMng->ChangeScene();
        
        ClearDrawScreen();		// ��ʂ̏�����
       
        if(sceneMng->GetNowScene() != nullptr)sceneMng->Draw();
        //key->Draw();

        ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f

        //�t���[�����[�g�̐ݒ�
        dNextTime += 1 / FPS * 1000;
        if (dNextTime > GetNowCount()) WaitTimer(static_cast<int>(dNextTime) - GetNowCount());
        else  dNextTime = GetNowCount(); //�␳
       
    }

    //����
    delete key;

    DxLib_End();	// DX���C�u�����g�p�̏I������

    return 0;	// �\�t�g�̏I��
}