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

#define BLOCK_SET_TIME 300


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
    int block_set_time;
    int treasure_num[TREASURE_TYPE_NUM];
    int bom_num;
};

struct DATA //座標,大きさ,スピードなどに使う
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
    BOM,//爆弾(最終的にはブロック)
    COIN,//コイン
    CUP,//カップ
    CROWN,//王冠
    JEWEL//宝石
};

enum class BLOCK_TYPE
{
    NONE,//ブロックが置けない
    BROKEN_BLOCK,//壊れそうなブロック
    WOUNDED_BLOCK,//傷ついているブロック
    NORMAL_BLOCK,//ブロック
    GENERATE_BLOCK,
    GROUND_BLOCK,//地面のブロック
    HARD_BLOCK,//かたいブロック
    VERY_HARD_BLOCK//とても固いブロック
};