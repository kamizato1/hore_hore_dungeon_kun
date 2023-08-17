#pragma once
#include "AbstractScene.h"

class Help : public AbstractScene
{
private:

	int image;
	int flashing_time;

	bool chane_title;

public:


	Help();


	void Update(Key* key) override;

	void Draw() const override;


	AbstractScene* ChangeScene() override;

};