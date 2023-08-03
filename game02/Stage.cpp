#include"DxLib.h"
#include"Stage.h"

Stage::Stage()
{
	LoadDivGraph("images/block01.png", 7, 7, 1, STAGE_BLOCK_SIZE_X, STAGE_BLOCK_SIZE_Y, block_image);
	LoadDivGraph("images/treasure.png", 4, 4, 1, 35, 35, treasure_image);

	FILE* fp_s;//ステージ１ファイル読み込み
	FILE* fp_t;//アイテム１ファイル読み込み
	fopen_s(&fp_s, "data/stage/stage02.txt", "r");
	fopen_s(&fp_t, "data/stage/treasure02.txt", "r");

	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)
		{
			int stage_type, treasure_type;
			fscanf_s(fp_s, "%d", &stage_type);
			fscanf_s(fp_t, "%d", &treasure_type);

			if (stage_type != -1)stageblock.emplace_back(j, i, stage_type, block_image[stage_type]);
			if (treasure_type != -1)treasure.emplace_back(j, i, treasure_type, treasure_image[treasure_type]);
		}
	}
	fclose(fp_s);
	fclose(fp_t);

	break_block_se = LoadSoundMem("bgm/breakblock3.mp3");
	LoadDivGraph("images/kakera_small.png", 10, 10, 1, 216, 216, break_block_image[0]);
	LoadDivGraph("images/kakera_big.png", 10, 10, 1, 216, 216, break_block_image[1]);
	caveat_image = LoadGraph("images/warning.png");

	pickaxe = nullptr;
}

Stage::~Stage()
{
	stageblock.clear();
	treasure.clear();
	breakblock.clear();
	bom.clear();
	delete pickaxe;
}

void Stage::Update()
{
	for (int i = 0; i < treasure.size(); i++)treasure[i].Update(this);  // 全要素に対するループ（宝物のアップデート）
	for (int i = 0; i < breakblock.size(); i++)
	{
		breakblock[i].Update();
		if(breakblock[i].CanDelete())breakblock.erase(breakblock.begin() + i);
	}
	for (int i = 0; i < stageblock.size(); i++)stageblock[i].SetHitEcplosion(FALSE);
	for (int i = 0; i < bom.size(); i++)
	{
		bom[i].Update(this);
		for (int j = 0; j < stageblock.size(); j++)
		{
			if (bom[i].HitExplosion(&stageblock[j]))
			{
				stageblock[j].SetHitEcplosion(TRUE);
			}
		}
		if (bom[i].CanDelete())
		{
			bom.erase(bom.begin() + i);
			for (int j = 0; j < stageblock.size(); j++)
			{
				if (stageblock[j].GetHitExplosion())
				{
					breakblock.emplace_back(stageblock[j].GetLocation(), break_block_image[1]);
					stageblock.erase(stageblock.begin() + j);
					j--;
				}
			}
		}
	}
	if (pickaxe != nullptr)
	{
		pickaxe->Update(this);
		if (pickaxe->CanDelete())pickaxe = nullptr;
	}
}

void Stage::Draw(float camera_work) const
{
	for (int i = 0; i < treasure.size(); i++) treasure[i].Draw(camera_work); // 全要素に対するループ(宝物の表示)
	for (int i = 0; i < stageblock.size(); i++)
	{
		stageblock[i].Draw(camera_work);  // 全要素に対するループ（ブロックの表示）
		if (stageblock[i].GetHitExplosion())DrawRotaGraph(stageblock[i].GetLocation().x + camera_work, stageblock[i].GetLocation().y, 1, 0, caveat_image, TRUE);
	}
	for (int i = 0; i < breakblock.size(); i++)breakblock[i].Draw(camera_work);
	for (int i = 0; i < bom.size(); i++)bom[i].Draw(camera_work);
	if (pickaxe != nullptr)pickaxe->Draw(camera_work);
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
				breakblock.emplace_back(stageblock[i].GetLocation(), break_block_image[1]);
				stageblock.erase(stageblock.begin() + i);
				PlaySoundMem(break_block_se, DX_PLAYTYPE_BACK, TRUE);
			}
			else if (type >= 5)return TRUE;//かたいブロックに当たったのでflgをTRUEにする
		}
	}
	return FALSE;
}

TREASURE_TYPE Stage::HitTreasure(BoxCollider* bc, bool can_delete)
{
	for (int i = 0; i < treasure.size(); i++)
	{
		if (treasure[i].HitBox(bc))
		{
			TREASURE_TYPE tt = treasure[i].GetTreasureType();
			if(can_delete)treasure.erase(treasure.begin() + i);
			return tt;
		}
	}
	return TREASURE_TYPE::NONE;
}

bool Stage::PutItem(DATA location, ITEM_TYPE item_type)
{
	int block_type = 0;
	int block_num = 0;
	bool exist_block = FALSE;
	for (int i = 0; i < stageblock.size(); i++)
	{
		DATA block_location = stageblock[i].GetLocation();
		if ((block_location.x == location.x) && (block_location.y == location.y))
		{
			exist_block = TRUE;
			block_num = i;
			block_type = static_cast<int>(stageblock[i].GetBlockType());
		}
	}

	if (item_type == ITEM_TYPE::PICKAXE)
	{
		if (exist_block)
		{
			if ((block_type > 0) && (block_type < 4))//ブロックが土だったら
			{
				if (--block_type == 0)
				{
					breakblock.emplace_back(stageblock[block_num].GetLocation(), break_block_image[1]);
					stageblock.erase(stageblock.begin() + block_num);
				}
				else
				{
					stageblock[block_num].SetBlockType(static_cast<BLOCK_TYPE>(block_type), block_image[block_type]);
					breakblock.emplace_back(stageblock[block_num].GetLocation(), break_block_image[0]);
				}
			}
		}
	}
	else if (item_type == ITEM_TYPE::BLOCK)
	{
		if (!exist_block)
		{
			int x = location.x / STAGE_BLOCK_SIZE_X;
			int y = location.y / STAGE_BLOCK_SIZE_Y;
			stageblock.emplace_back(x, y, 4, block_image[4]);
			if (HitTreasure(&stageblock[stageblock.size() - 1], FALSE) != TREASURE_TYPE::NONE)
			{
				stageblock.erase(stageblock.end() - 1);
				return FALSE;
			}
			return TRUE;
		}
	}
	else
	{
		if (!exist_block)
		{
			int x = location.x / STAGE_BLOCK_SIZE_X;
			int y = location.y / STAGE_BLOCK_SIZE_Y;
			stageblock.emplace_back(x, y, 4, block_image[4]);
			TREASURE_TYPE hit_item = HitTreasure(&stageblock[stageblock.size() - 1], FALSE);
			stageblock.erase(stageblock.end() - 1);
			if (hit_item == TREASURE_TYPE::NONE)
			{
				bom.emplace_back(location, DATA{0,0});
				return TRUE;
			}
		}
	}
	
	return FALSE;
}


void Stage::ThrowItem(DATA location, DATA speed, ITEM_TYPE item_type)
{
	if (item_type == ITEM_TYPE::PICKAXE)
	{
		if (pickaxe == nullptr)pickaxe = new Pickaxe(location, speed);
	}
	else if (item_type == ITEM_TYPE::BLOCK)
	{
		
	}
	else
	{
		bom.emplace_back(location, speed);
	}
}

