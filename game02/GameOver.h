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
	bool change_scene;
	int stage_num;
	int wait_time;

public:

	GameOver(int stage_num);
	void Update(Key* key) override;
	void Draw() const override;
	AbstractScene* ChangeScene() override;
};
