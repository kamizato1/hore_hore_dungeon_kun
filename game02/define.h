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
    NONE = -1,
    KEY,
    BAG,
    BOM,
};