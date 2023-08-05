#pragma once

#include"BoxCollider.h"
#include"define.h"

enum class BLOCK_TYPE
{
    NONE,//�u���b�N���u���Ȃ�
    BROKEN_BLOCK,//��ꂻ���ȃu���b�N
    WOUNDED_BLOCK,//�����Ă���u���b�N
    NORMAL_BLOCK,//�u���b�N
    GROUND_BLOCK,//�n�ʂ̃u���b�N
    HARD_BLOCK,//�������u���b�N
    VERY_HARD_BLOCK//�ƂĂ��ł��u���b�N
};

class StageBlock : public BoxCollider
{
private:

    BLOCK_TYPE type;
    int image;
    int caveat_image;
    bool hit_explosion;

public:

    StageBlock(int x, int y, BLOCK_TYPE type, int image, int caveat_image);

    //�`��ȊO�̍X�V����������
    void Update();
    //�`��Ɋւ��邱�Ƃ���������
    void Draw(float camera_work) const;

    BLOCK_TYPE GetBlockType() { return type; }
    void SetBlockType(BLOCK_TYPE type, int image);
    void SetHitEcplosion(bool flg) { hit_explosion = flg; }
};