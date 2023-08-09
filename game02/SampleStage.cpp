#include"DxLib.h"
#include"SampleStage.h"

#define SAMPLE_STAGE_BLOCK_NUM_X 35

SampleStage::SampleStage()
{
	Init();

	FILE* fp_s;//ステージ１ファイル読み込み
	fopen_s(&fp_s, "data/stage/samplestage.txt", "r");

	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)
	{
		for (int j = 0; j < SAMPLE_STAGE_BLOCK_NUM_X; j++)
		{
			int block_type;
			fscanf_s(fp_s, "%d", &block_type);

			DATA location;
			location.x = (j * BLOCK_SIZE_X) + (BLOCK_SIZE_X / 2);
			location.y = (i * BLOCK_SIZE_Y) + (BLOCK_SIZE_Y / 2);

			if (block_type != -1)stageblock.emplace_back(location, block_type);
		}
	}
	fclose(fp_s);

	pickaxe = nullptr;
}

SampleStage::~SampleStage()
{
	stageblock.clear();
	treasure.clear();
	effect.clear();
	bom.clear();
	delete pickaxe;
}