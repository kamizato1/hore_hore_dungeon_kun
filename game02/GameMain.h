#pragma once

#include"Key.h"
#include"Player.h"
#include"StageBase.h"
#include"AbstractScene.h"
#include"Ui.h"
#include"define.h"

class GameMain : public AbstractScene
{
private:

    bool stop;

    StageBase* stagebase;
    Player* player;
    Ui* ui;

    int back_ground_image[3];
    int life;
    int time;

public:

    GameMain();
    ////�f�X�g���N�^
    ~GameMain();

    //�`��ȊO�̍X�V����������
    void Update(Key* key) override;
    //�`��Ɋւ��邱�Ƃ���������
    void Draw() const override;
    AbstractScene* ChangeScene() override;

};