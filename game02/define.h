#pragma once

#define STAGE_NUM 5

#define FPS 60

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define KEY_NUM 11

#define STAGE_BLOCK_NUM_Y 20

#define BLOCK_SIZE_X 36.0f
#define BLOCK_SIZE_Y 36.0f

#define ITEM_TYPE_NUM 3
#define TREASURE_TYPE_NUM 5
#define BLOCK_TYPE_NUM 8

#define GRAVITY_POWER 0.3f

#define MAX_FALL_SPEED 5.0f




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

struct PLAYER_UI
{
    int item_type;
    float now_item_set_time[ITEM_TYPE_NUM];
    float item_set_time[ITEM_TYPE_NUM];
    int treasure_num[TREASURE_TYPE_NUM];
    int break_block_num;
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
    //0�Ԗڂ͐������ꂽ�u���b�N
    COIN = 1,//�R�C��
    CUP,//�J�b�v
    CROWN,//����
    JEWEL//���
};

enum class BLOCK_TYPE
{
    NONE,//�u���b�N���u���Ȃ�
    BROKEN_BLOCK,//��ꂻ���ȃu���b�N
    WOUNDED_BLOCK,//�����Ă���u���b�N
    NORMAL_BLOCK,//�u���b�N
    GENERATE_BLOCK,
    GROUND_BLOCK,//�n�ʂ̃u���b�N
    HARD_BLOCK,//�������u���b�N
    VERY_HARD_BLOCK//�ƂĂ��ł��u���b�N
};