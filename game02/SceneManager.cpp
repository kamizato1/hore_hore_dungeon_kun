#include"DxLib.h"
#include<stdio.h>

#include"SceneManager.h"
#include"AbstractScene.h"

SceneManager::SceneManager(AbstractScene* scene)
{
	mScene = scene;  //m_Scene �� �V�[���|�C���^�^�̕ϐ��@���ݕ\������V�[��������
}

void SceneManager::Update(Key* key)
{
	//InputManager::Update();
	if(mScene != nullptr)mScene->Update(key);//���������Ă�V�[����update�����
}

void SceneManager::Draw()const
{
	if (mScene != nullptr)mScene->Draw();//���������Ă�V�[����Draw�����
}



void SceneManager::ChangeScene()
{
	AbstractScene* next = mScene->ChangeScene();  //���̃V�[���ƌ��݂̃V�[�����ׂ� // -> �A���[���Z�q�@�|�C���^�̐�̂�ɃA�N�Z�X����@m_Scene->ChangeScene
	if (next != mScene)//��̃V�[�����Ⴄ�Ȃ�
	{
		mScene->Delete();
		delete mScene; //new�ŏ������񂾂̂�delete�ŏ���
		mScene = next; //	next	������
	}
}