#include<stdio.h>
#include"SceneManager.h"
#include"AbstractScene.h"

SceneManager::SceneManager(AbstractScene* scene)
{
	mScene = scene;  //m_Scene ← シーンポインタ型の変数　現在表示するシーンを入れる
}

void SceneManager::Update(Key* key)
{
	//InputManager::Update();
	mScene->Update(key);//今動かしてるシーンのupdateをやる
}

void SceneManager::Draw()const
{
	mScene->Draw();//今動かしてるシーンのDrawをやる
}

void SceneManager::ChangeScene()
{
	AbstractScene* next = mScene->ChangeScene();  //次のシーンと現在のシーンを比べる // -> アロー演算子　ポインタの先のやつにアクセスする　m_Scene->ChangeScene
	if (next != mScene)//二つのシーンが違うなら
	{
		delete mScene; //newで書き込んだのはdeleteで消す
		mScene = next; //	next	を入れる
	}
}