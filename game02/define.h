#pragma once

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define KEY_NUM 10

#define STAGE_BLOCK_NUM_X 100
#define STAGE_BLOCK_NUM_Y 20

#define STAGE_BLOCK_SIZE_X 36
#define STAGE_BLOCK_SIZE_Y 36

#define GRAVITY_POWER 0.4

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
    R
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
    KEY,
    BAG,
    BOM,
    ANGRY_BOM
};