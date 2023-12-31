#pragma once
#include"Key.h"

class AbstractScene
{
public:

	virtual void Delete() = 0;

	//描画以外の更新を実装する
	virtual void Update(Key* key) = 0;

	//描画に関することを実装する
	virtual void Draw() const = 0;
	virtual AbstractScene* ChangeScene() = 0;
};

