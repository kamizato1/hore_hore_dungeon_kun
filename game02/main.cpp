/********************************************************************
//メイン
********************************************************************/
#include "DxLib.h"

#include"Key.h"
#include"Title.h"
#include"GameMain.h"
#include"SceneManager.h"
#include"define.h"

//テスト(デバック)
#include"Result.h"
#include"Help.h"


/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    double dNextTime = GetNowCount();

    // タイトルを test に変更
    SetMainWindowText("惚れ掘れダンジョン君");

    ChangeWindowMode(TRUE);		// ウィンドウモードで起動

    SetAlwaysRunFlag(true);

    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

    if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

    
    SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

    SetFontSize(20);		// 文字サイズを設定

    SceneManager* sceneMng = new SceneManager(new GameMain());
    Key* key = new Key();

    while ((ProcessMessage() == 0) && (sceneMng->GetNowScene() != nullptr))
    {
        sceneMng->Update(key);
        key->Update();
        sceneMng->ChangeScene();
        
        ClearDrawScreen();		// 画面の初期化
       
        if(sceneMng->GetNowScene() != nullptr)sceneMng->Draw();
        //key->Draw();

        ScreenFlip();			// 裏画面の内容を表画面に反映

        //フレームレートの設定
        dNextTime += 1 / FPS * 1000;
        if (dNextTime > GetNowCount()) WaitTimer(static_cast<int>(dNextTime) - GetNowCount());
        else  dNextTime = GetNowCount(); //補正
       
    }

    //消去
    delete key;

    DxLib_End();	// DXライブラリ使用の終了処理

    return 0;	// ソフトの終了
}