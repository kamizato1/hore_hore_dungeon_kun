#include"DxLib.h"
#include"StageBase.h"

void StageBase::Init()
{
	break_block_se = LoadSoundMem("bgm/breakblock3.mp3");
	hit_pickaxe_se = LoadSoundMem("bgm/hitpickaxe2.mp3");
	LoadDivGraph("images/kakera_small.png", 10, 10, 1, 216, 216, effect_image[0]);
	LoadDivGraph("images/kakera_big.png", 10, 10, 1, 216, 216, effect_image[1]);
	LoadDivGraph("images/kakera_iwa.png", 10, 10, 1, 216, 216, effect_image[2]);
	LoadDivGraph("images/kakera_yuka.png", 10, 10, 1, 216, 216, effect_image[3]);
	LoadDivGraph("images/explosion.png", 9, 9, 1, 320, 320, explosion_image);
	pickaxe_image = LoadGraph("images/pickaxe.png");
}

void StageBase::Update()
{
	for (int i = 0; i < treasure.size(); i++)
	{
		treasure[i].Update(this);  // 全要素に対するループ（宝物のアップデート）
		if (treasure[i].GetCanDelete())treasure.erase(treasure.begin() + i);
	}
	for (int i = 0; i < stageblock.size(); i++)stageblock[i].SetHitEcplosion(FALSE);
	for (int i = 0; i < bom.size(); i++)
	{
		bom[i].Update(this);
		HitBlastRange(i);
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

void StageBase::HitBlastRange(int bom_num)
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


void StageBase::Draw1(float camera_work) const
{
	for (int i = 0; i < treasure.size(); i++) treasure[i].Draw(camera_work); // 全要素に対するループ(宝物の表示)
	for (int i = 0; i < stageblock.size(); i++)stageblock[i].Draw(camera_work);  // 全要素に対するループ（ブロックの表示）
}

void StageBase::Draw2(float camera_work) const
{
	for (int i = 0; i < effect.size(); i++)effect[i].Draw(camera_work);
	for (int i = 0; i < bom.size(); i++)bom[i].Draw(camera_work);
	if (pickaxe != nullptr)pickaxe->Draw(camera_work);
}

bool StageBase::HitStage(BoxCollider* bc)
{
	for (int i = 0; i < stageblock.size(); i++)  // 全要素に対するループ
	{
		if (stageblock[i].HitBox(bc))
		{
			if (stageblock[i].GetBlockType() != BLOCK_TYPE::NONE)return TRUE;
		}
	}
	return FALSE;
}

bool StageBase::HitPickaxe(BoxCollider* bc)
{
	for (int i = 0; i < bom.size(); i++)
	{
		if (bom[i].HitBox(bc))
		{
			if (bom[i].HitDamage())bom[i].SetCanDelete(TRUE);
		}
		else bom[i].SetOldHit(FALSE);
	}
	for (int i = 0; i < treasure.size(); i++)
	{
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

bool StageBase::HitBom(BoxCollider* bc)
{
	for (int i = 0; i < bom.size(); i++)
	{
		if (bom[i].HitBox(bc))return TRUE;
	}
	return FALSE;
}

TREASURE_TYPE StageBase::GetTreasure(BoxCollider* bc)
{
	for (int i = 0; i < treasure.size(); i++)
	{
		if (treasure[i].HitBox(bc))
		{
			TREASURE_TYPE treasure_type = treasure[i].GetTreasureType();
			treasure.erase(treasure.begin() + i);
			return treasure_type;
		}
	}
	return TREASURE_TYPE::NONE;
}

bool StageBase::HitTreasure(BoxCollider* bc)
{
	for (int i = 0; i < treasure.size(); i++)
	{
		if (treasure[i].HitBox(bc))return TRUE;
	}
	return FALSE;
}


bool StageBase::PutItem(DATA location, ITEM_TYPE item_type)
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
					stageblock[block_num].SetBlockType(block_type);

				}
			}
		}
	}
	else if (item_type == ITEM_TYPE::BLOCK)
	{
		if (!exist_block)
		{
			stageblock.emplace_back(location, 4);
			if (!(HitTreasure(&stageblock[stageblock.size() - 1])) && !(HitBom(&stageblock[stageblock.size() - 1])))return TRUE;
			else stageblock.erase(stageblock.end() - 1);
		}
	}
	else
	{
		if (!exist_block)
		{
			stageblock.emplace_back(location, 4);
			if (!(HitTreasure(&stageblock[stageblock.size() - 1])) && !(HitBom(&stageblock[stageblock.size() - 1])))
			{
				stageblock.erase(stageblock.end() - 1);
				bom.emplace_back(location, DATA{ 0,0 });
				return TRUE;
			}
			else stageblock.erase(stageblock.end() - 1);
		}
	}

	return FALSE;
}

void StageBase::ThrowItem(DATA location, DATA speed, ITEM_TYPE item_type)
{
	if (item_type == ITEM_TYPE::PICKAXE)
	{
		if (pickaxe == nullptr)pickaxe = new Pickaxe(location, speed, pickaxe_image, hit_pickaxe_se);
	}
	else if (item_type == ITEM_TYPE::BLOCK)
	{

	}
	else
	{
		bom.emplace_back(location, speed);
	}
}
