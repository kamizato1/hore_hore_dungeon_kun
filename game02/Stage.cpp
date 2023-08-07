#include"DxLib.h"
#include"Stage.h"

Stage::Stage()
{
	int treasure_image[3];

	break_block_se = LoadSoundMem("bgm/breakblock3.mp3");
	LoadDivGraph("images/kakera_small.png", 10, 10, 1, 216, 216, effect_image[0]);
	LoadDivGraph("images/kakera_big.png", 10, 10, 1, 216, 216, effect_image[1]);
	LoadDivGraph("images/kakera_iwa.png", 10, 10, 1, 216, 216, effect_image[2]);
	LoadDivGraph("images/kakera_yuka.png", 10, 10, 1, 216, 216, effect_image[3]);
	LoadDivGraph("images/block01.png", 7, 7, 1, BLOCK_SIZE_X, BLOCK_SIZE_Y, block_image);
	LoadDivGraph("images/treasure1.png", 3, 3, 1, 36, 36, treasure_image);
	LoadDivGraph("images/explosion.png", 9, 9, 1, 320, 320, explosion_image);
	caveat_image = LoadGraph("images/warning.png");

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

			if (block_type != -1)stageblock.emplace_back(j, i, static_cast<BLOCK_TYPE>(block_type), block_image[block_type], caveat_image);
			if (treasure_type != -1)treasure.emplace_back(j, i, static_cast<TREASURE_TYPE>(treasure_type), treasure_image[treasure_type]);
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

void Stage::Update()
{
	for (int i = 0; i < treasure.size(); i++)
	{
		treasure[i].Update(this);  // 全要素に対するループ（宝物のアップデート）
		if(treasure[i].GetCanDelete())treasure.erase(treasure.begin() + i);
	}
	for (int i = 0; i < stageblock.size(); i++)stageblock[i].SetHitEcplosion(FALSE);
	for (int i = 0; i < bom.size(); i++)
	{
		bom[i].Update(this);
		HitBom(i);
	}
	if (pickaxe != nullptr)
	{
		pickaxe->Update(this);
		if (pickaxe->GetCanDelete())pickaxe = nullptr;
	}
	for (int i = 0; i < effect.size(); i++)
	{
		effect[i].Update();
		if (effect[i].CanDelete())effect.erase(effect.begin() + i);
	}
}


void Stage::HitBom(int bom_num)
{
	if (bom[bom_num].GetCanDelete())
	{
		for (int i = 0; i < bom.size(); i++)
		{
			if (bom[bom_num].HitExplosion(&bom[i]))bom[i].SetCanDelete(TRUE);
		}
		for (int i = 0; i < treasure.size(); i++)
		{
			if ((bom[bom_num].HitExplosion(&treasure[i])) && (treasure[i].HitDamage(FALSE, this)))
			{
				if (treasure[i].GetTreasureType() == TREASURE_TYPE::BOM)
				{
					bom.emplace_back(treasure[i].GetLocation(), DATA{ 0,0 });
				}
				treasure.erase(treasure.begin() + i);
				i--;
			}
		}
	}

	for (int i = 0; i < stageblock.size(); i++)
	{
		if (bom[bom_num].HitExplosion(&stageblock[i]))
		{
			BLOCK_TYPE block_type = stageblock[i].GetBlockType();
			if ((block_type != BLOCK_TYPE::VERY_HARD_BLOCK) && (block_type != BLOCK_TYPE::NONE))
			{
				if (bom[bom_num].GetCanDelete())
				{
					int effect_image_type = 1;
					if (block_type == BLOCK_TYPE::HARD_BLOCK)effect_image_type = 2;
					else if (block_type == BLOCK_TYPE::GROUND_BLOCK)effect_image_type = 3;
					effect.emplace_back(stageblock[i].GetLocation(), effect_image[effect_image_type], BREAK_BLOCK_IMAGE_NUM);
					stageblock.erase(stageblock.begin() + i);
					i--;
				}
				else stageblock[i].SetHitEcplosion(TRUE);
			}
		}
	}
	if (bom[bom_num].GetCanDelete())
	{
		effect.emplace_back(bom[bom_num].GetLocation(), explosion_image, EXPLOSION_IMAGE_NUM);
		bom.erase(bom.begin() + bom_num);
	}
	else if (bom[bom_num].GetLocation().y > SCREEN_HEIGHT + 200)bom.erase(bom.begin() + bom_num);
}


void Stage::Draw1(float camera_work) const
{
	for (int i = 0; i < treasure.size(); i++) treasure[i].Draw(camera_work); // 全要素に対するループ(宝物の表示)
	for (int i = 0; i < stageblock.size(); i++)stageblock[i].Draw(camera_work);  // 全要素に対するループ（ブロックの表示）
}

void Stage::Draw2(float camera_work) const
{
	for (int i = 0; i < effect.size(); i++)effect[i].Draw(camera_work);
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
	for (int i = 0; i < treasure.size(); i++)
	{
		for (int i = 0; i < bom.size(); i++)
		{
			if (bom[i].HitBox(bc))
			{
				if (bom[i].HitDamage())bom[i].SetCanDelete(TRUE);
			}
			else bom[i].SetOldHit(FALSE);
		}
		if (treasure[i].HitBox(bc))
		{
			if (treasure[i].HitDamage(TRUE, this))
			{
				if (treasure[i].GetTreasureType() == TREASURE_TYPE::BOM)
				{
					bom.emplace_back(treasure[i].GetLocation(), DATA{ 0,0 });
					bom[bom.size() - 1].SetOldHit(TRUE);
				}
				treasure.erase(treasure.begin() + i);
				i--;
			}
		}
		else treasure[i].SetOldHit(FALSE);
	}
	

	for (int i = 0; i < stageblock.size(); i++)  // 全要素に対するループ
	{
		if (stageblock[i].HitBox(bc))
		{
			int block_type = static_cast<int>(stageblock[i].GetBlockType());
			if ((block_type >= 1) && (block_type <= 4))//ブロックが土だったら
			{
				int effect_image_type = 1;
				if (block_type == 4)effect_image_type = 3;
				effect.emplace_back(stageblock[i].GetLocation(), effect_image[effect_image_type], BREAK_BLOCK_IMAGE_NUM);
				stageblock.erase(stageblock.begin() + i);
				PlaySoundMem(break_block_se, DX_PLAYTYPE_BACK, TRUE);
			}
			else if (block_type >= 5)return TRUE;//かたいブロックに当たったのでflgをTRUEにする
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
			TREASURE_TYPE treasure_type = treasure[i].GetTreasureType();
			if(can_delete)treasure.erase(treasure.begin() + i);
			return treasure_type;
		}
	}
	return TREASURE_TYPE::NONE;
}

bool Stage::PutItem(DATA location, ITEM_TYPE item_type)
{
	int x = location.x / BLOCK_SIZE_X;
	int y = location.y / BLOCK_SIZE_Y;
	int block_type = 0;
	int block_num = 0;
	bool exist_block = FALSE;
	DATA radius = { 1,1 };
	for (int i = 0; i < stageblock.size(); i++)
	{
		if (stageblock[i].HitBox(&stageblock[i], location, radius))
		{
			exist_block = TRUE;
			block_num = i;
			block_type = static_cast<int>(stageblock[i].GetBlockType());
			break;
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
					effect.emplace_back(stageblock[block_num].GetLocation(), effect_image[1], BREAK_BLOCK_IMAGE_NUM);
					stageblock.erase(stageblock.begin() + block_num);
				}
				else
				{
					effect.emplace_back(stageblock[block_num].GetLocation(), effect_image[0], BREAK_BLOCK_IMAGE_NUM);
					stageblock[block_num].SetBlockType(static_cast<BLOCK_TYPE>(block_type), block_image[block_type]);
					
				}
			}
		}
	}
	else if (item_type == ITEM_TYPE::BLOCK)
	{
		if (!exist_block)
		{
			stageblock.emplace_back(x, y, BLOCK_TYPE::GROUND_BLOCK, block_image[4], caveat_image);
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
			stageblock.emplace_back(x, y, BLOCK_TYPE::GROUND_BLOCK, block_image[4], caveat_image);
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
