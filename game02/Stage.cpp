#include"DxLib.h"
#include"Stage.h"

Stage::Stage()
{
	LoadDivGraph("images/block02.png", 7, 7, 1, STAGE_BLOCK_SIZE_X, STAGE_BLOCK_SIZE_Y, block_image);

	for (int i = 0; i < 15; i++)item[i] = nullptr;;
	int item_count = 0;
	int block_count = 0;

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

			if (stage_type != -1)stageblock.emplace_back(j, i, stage_type, block_image[stage_type]);
			//if (item_type != 0)item[count] = nullptr;
		}
	}
	fclose(fp_s);
	fclose(fp_i);

	break_block_se = LoadSoundMem("bgm/breakblock3.mp3");
}

Stage::~Stage()
{
	stageblock.clear();
}

void Stage::Update()
{
}

void Stage::Draw(float camera_work) const
{
	for (int i = 0; i < stageblock.size(); i++)  // 全要素に対するループ
	{     
		stageblock[i].Draw(camera_work);
	}

	DrawFormatString(0, 50, 0xffffff, "%d", stageblock.size());
}

bool Stage::HitStage(BoxCollider* bc)
{
	for (int i = 0; i < stageblock.size(); i++)  // 全要素に対するループ
	{
		if (stageblock[i].HitBox(bc))
		{
			if(stageblock[i].GetBlockType() != BLOCK_TYPE::NONE)return TRUE;
		}
	}
	return FALSE;
}

bool Stage::HitPickaxe(BoxCollider* bc)
{
	for (int i = 0; i < stageblock.size(); i++)  // 全要素に対するループ
	{
		if (stageblock[i].HitBox(bc))
		{
			int type = static_cast<int>(stageblock[i].GetBlockType());
			if ((type > 0) && (type < 5))//ブロックが土だったら
			{
				stageblock.erase(stageblock.begin() + i);;
				PlaySoundMem(break_block_se, DX_PLAYTYPE_BACK, TRUE);
			}
			else if (type >= 5)return TRUE;//かたいブロックに当たったのでflgをTRUEにする
		}
	}
	return FALSE;
}

bool Stage::UseItem(DATA location, ITEM_TYPE item_type)
{
	if (item_type == ITEM_TYPE::PICKAXE)
	{
		for (int i = 0; i < stageblock.size(); i++)
		{
			DATA block_location = stageblock[i].GetLocation();
			if ((block_location.x == location.x) && (block_location.y == location.y))
			{
				int type = static_cast<int>(stageblock[i].GetBlockType());
				if ((type > 0) && (type < 4))//ブロックが土だったら
				{
					if (--type == 0)stageblock.erase(stageblock.begin() + i);
					else stageblock[i].SetBlockType(static_cast<BLOCK_TYPE>(type), block_image[type]);
					//PlaySoundMem(break_block_se, DX_PLAYTYPE_BACK, TRUE);
				}
			}
		}		
	}
	else if (item_type == ITEM_TYPE::BLOCK)
	{
		for (int i = 0; i < stageblock.size(); i++)
		{
			DATA block_location = stageblock[i].GetLocation();
			if ((block_location.x == location.x) && (block_location.y == location.y))return FALSE;
		}
		int x = location.x / 30;
		int y = location.y / 30;
		stageblock.emplace_back(x, y, 4, block_image[4]);
	}

	return true;
}