#pragma once
#include"Key.h"

class AbstractScene
{
public:

	virtual void Delete() = 0;

	//�`��ȊO�̍X�V����������
	virtual void Update(Key* key) = 0;

	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw() const = 0;
	virtual AbstractScene* ChangeScene() = 0;
};

