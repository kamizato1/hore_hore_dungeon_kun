#include"DxLib.h"
#include"Stage.h"

Stage::Stage()
{
	Init();

	FILE* fp_s;//ステージ１ファイル読み込み
	FILE* fp_t;//アイテム１ファイル読み込み
	fopen_s(&fp_s, "data/stage/stage02.txt", "r");
	fopen_s(&fp_t, "data/stage/treasure02.txt", "r");

	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)
		{
			int block_type, treasure_type;
			fscanf_s(fp_s, "%d", &block_type);
			fscanf_s(fp_t, "%d", &treasure_type);

			DATA location;
			location.x = (j * BLOCK_SIZE_X) + (BLOCK_SIZE_X / 2);
			location.y = (i * BLOCK_SIZE_Y) + (BLOCK_SIZE_Y / 2);

			if (block_type != -1)stageblock.emplace_back(location, block_type);
			if (treasure_type != -1)treasure.emplace_back(location, treasure_type);
		}
	}
	fclose(fp_s);
	fclose(fp_t);

	pickaxe = nullptr;
}

Stage::~Stage()
{
	stageblock.clear();
	treasure.clear();
	effect.clear();
	bom.clear();
	delete pickaxe;
}