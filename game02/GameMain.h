#pragma once

#include"Key.h"
#include"Player.h"
#include"Stage.h"
#include"AbstractScene.h"
#include"Ui.h"
#include"define.h"

class GameMain : public AbstractScene
{
private:

    Stage* stage;
    Player* player;
    Ui* ui;

    float camera_work_record[20];
    float camera_work;

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