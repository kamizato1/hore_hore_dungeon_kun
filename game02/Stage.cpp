#include"DxLib.h"
#include"Stage.h"

Stage::Stage()
{
	LoadDivGraph("images/block02.png", 7, 7, 1, STAGE_BLOCK_SIZE_X, STAGE_BLOCK_SIZE_Y, block_image);

	for (int i = 0; i < 15; i++)item[i] = nullptr;;
	int count = 0;

	FILE* fp_s;//ステージ１ファイル読み込み
	FILE* fp_i;//アイテム１ファイル読み込み
	fopen_s(&fp_s, "data/stage/stage01.txt", "r");
	fopen_s(&fp_i, "data/stage/item01.txt", "r");

	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)
		{
			int stage_type, item_type;
			fscanf_s(fp_s, "%d", &stage_type);
			fscanf_s(fp_i, "%d", &item_type);

			if (stage_type == -1)stageblock[i][j] = nullptr;
			else stageblock[i][j] = new StageBlock(j, i, stage_type, block_image[stage_type]);

			if (item_type != 0)item[count] = nullptr;
		}
	}
	fclose(fp_s);

	break_block_se = LoadSoundMem("bgm/breakblock3.mp3");
	
}

Stage::~Stage()
{
	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)
		{
			delete  stageblock[i][j];
		}
	}
}

void Stage::Update()
{
}

void Stage::Draw(float camera_work) const
{
	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)
		{
			if(stageblock[i][j] != nullptr)stageblock[i][j]->Draw(camera_work);
		}
	}
}

bool Stage::HitStage(BoxCollider* bc)
{
	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)
		{
			if (stageblock[i][j] != nullptr)
			{
				if (stageblock[i][j]->HitBox(bc))
				{
					if (stageblock[i][j]->GetBlockType() != BLOCK_TYPE::NONE)return TRUE;
				}
			}
		}
	}
	return FALSE;
}

bool Stage::HitPickaxe(BoxCollider* bc)
{
	//bool flg = FALSE;//かたいブロックに当たったか

	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)
		{
			if (stageblock[i][j] != nullptr)
			{
				if (stageblock[i][j]->HitBox(bc))
				{
					int type = static_cast<int>(stageblock[i][j]->GetBlockType());
					if ((type > 0) && (type < 5))//ブロックが土だったら
					{
						stageblock[i][j] = nullptr;
						PlaySoundMem(break_block_se, DX_PLAYTYPE_BACK, TRUE);
					}
					else if (type >= 5)return TRUE;//かたいブロックに当たったのでflgをTRUEにする
				}
			}
		}
	}
	return FALSE;
}


void Stage::UseItem(int x, int y, ITEM_TYPE item_type)
{
	if (item_type == ITEM_TYPE::PICKAXE)
	{
		if (stageblock[y][x] != nullptr)
		{
			int type = static_cast<int>(stageblock[y][x]->GetBlockType());
			if ((type > 0) && (type < 4))//ブロックが土だったら
			{
				if (--type == 0)stageblock[y][x] = nullptr;
				else stageblock[y][x]->SetBlockType(static_cast<BLOCK_TYPE>(type), block_image[type]);
				PlaySoundMem(break_block_se, DX_PLAYTYPE_BACK, TRUE);
			}
		}
	}
	else if (item_type == ITEM_TYPE::BLOCK)
	{
		if (stageblock[y][x] == nullptr)
		{
			stageblock[y][x] = new StageBlock(x, y, 4, block_image[4]);
		}
	}
}