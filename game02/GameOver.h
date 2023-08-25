#pragma once
#include"AbstractScene.h"
#include"define.h"

#define FONT_NUM 8

class GameOver : public AbstractScene
{
private:

	DATA font_location[FONT_NUM];
	int font_image[FONT_NUM];
	int back_ground_image;
	int font_angle[FONT_NUM];

public:

	GameOver();
	void Update(Key* key) override;
	void Draw() const override;
	AbstractScene* ChangeScene() override;
};
