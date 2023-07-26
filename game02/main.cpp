/********************************************************************
//メイン
********************************************************************/
#include "DxLib.h"

#include"Key.h"
#include"Title.h"
#include"GameMain.h"
#include"SceneManager.h"
#include"define.h"
#include"FpsControll.h"

/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {

    // タイトルを test に変更
    SetMainWindowText("惚れ掘れダンジョン君");

    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);
    ChangeWindowMode(TRUE);		// ウィンドウモードで起動

    SetWaitVSyncFlag(0);

    if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

    SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

    SetFontSize(20);		// 文字サイズを設定

    SceneManager* sceneMng = new SceneManager(new GameMain());
    Key* key = new Key();

    while (ProcessMessage() == 0)
    {
        FpsControll_Update();

        key->Update();

        sceneMng->Update(key);

        ClearDrawScreen();		// 画面の初期化

        sceneMng->Draw();

        //フレームレート表示
        FpsControll_Draw();

        sceneMng->ChangeScene();
        
        ScreenFlip();			// 裏画面の内容を表画面に反映

        //待機
        FpsControll_Wait();
    }


    DxLib_End();	// DXライブラリ使用の終了処理

    return 0;	// ソフトの終了
}