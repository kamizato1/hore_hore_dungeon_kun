#pragma once
#include"AbstractScene.h"
#include"Key.h"

class SceneManager
{
private:
	AbstractScene* mScene;  //現在のシーン

public:
	//コンストラクタ
	SceneManager(AbstractScene* scene);

	//デストラクタ
	/*~SceneManager()
	{
		delete mScene;
	}*/

	//描画以外の更新を実装する
	void Update(Key* key);

	//描画に関することを実装する
	void Draw() const;

	void ChangeScene();

	AbstractScene* GetNowScene() { return mScene; }
};