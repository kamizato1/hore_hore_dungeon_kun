#pragma once

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define KEY_NUM 10

#define STAGE_BLOCK_NUM_X 100
#define STAGE_BLOCK_NUM_Y 21

#define STAGE_BLOCK_SIZE_X 30
#define STAGE_BLOCK_SIZE_Y 30

#define MINI_MAP_SIZE_X 15
#define MINI_MAP_SIZE_Y 15

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
    KEY = 1,
    BAG,
    BOM,
    ANGRY_BOM

};