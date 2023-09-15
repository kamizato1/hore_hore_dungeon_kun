#pragma once
#include"Key.h"

class AbstractScene
{
public:

	virtual void Delete() = 0;

	//•`‰æˆÈŠO‚ÌXV‚ğÀ‘•‚·‚é
	virtual void Update(Key* key) = 0;

	//•`‰æ‚ÉŠÖ‚·‚é‚±‚Æ‚ğÀ‘•‚·‚é
	virtual void Draw() const = 0;
	virtual AbstractScene* ChangeScene() = 0;
};

