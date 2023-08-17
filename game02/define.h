#pragma once

#define FPS 60

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define KEY_NUM 11

#define STAGE_BLOCK_NUM_X 100
#define STAGE_BLOCK_NUM_Y 20

#define BLOCK_SIZE_X 36
#define BLOCK_SIZE_Y 36

#define ITEM_TYPE_NUM 3

#define GRAVITY_POWER 0.4

#define MAX_FALL_SPEED 10

enum
{
    A,
    B,
    X,
    Y,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    L,
    R,
    START
};

struct DATA //���W,�傫��,�X�s�[�h�ȂǂɎg��
{
    float x, y;
};

enum class ITEM_TYPE
{
    PICKAXE,
    BLOCK,
    BOM
};

enum class TREASURE_TYPE
{
    KEY,
    BAG,
    BOM,
};

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