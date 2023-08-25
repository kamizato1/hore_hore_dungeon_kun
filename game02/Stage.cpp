#include"DxLib.h"
#include"Stage.h"

Stage::Stage()
{
	Init();

	FILE* fp_s;//ステージ１ファイル読み込み
	FILE* fp_t;//アイテム１ファイル読み込み
	fopen_s(&fp_s, "data/stage/stage01.txt", "r");
	fopen_s(&fp_t, "data/stage/treasure01.txt", "r");

	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)
	{
		for (int j = 0; j < STAGE_BLOCK_NUM_X; j++)
		{
			int block_type, treasure_type;
			fscanf_s(fp_s, "%d", &block_type);
			fscanf_s(fp_t, "%d", &treasure_type);

			DATA location;
			location.x = ((j - 1) * BLOCK_SIZE_X) + (BLOCK_SIZE_X / 2);
			location.y = (i * BLOCK_SIZE_Y) + (BLOCK_SIZE_Y / 2);

			if (block_type != -1)block.emplace_back(location, block_type);
			if (treasure_type != -1)treasure.emplace_back(location, treasure_type);
		}
	}
	fclose(fp_s);
	fclose(fp_t);

	pickaxe = nullptr;
}

Stage::~Stage()
{
	block.clear();
	treasure.clear();
	effect.clear();
	bom.clear();
	delete pickaxe;
}

void Stage::Init()
{
	break_block_se = LoadSoundMem("bgm/breakblock3.mp3");
	hit_pickaxe_se = LoadSoundMem("bgm/hitpickaxe2.mp3");
	LoadDivGraph("images/kakera_small.png", 10, 10, 1, 216, 216, effect_image[0]);
	LoadDivGraph("images/kakera_big.png", 10, 10, 1, 216, 216, effect_image[1]);
	LoadDivGraph("images/kakera_iwa.png", 10, 10, 1, 216, 216, effect_image[2]);
	LoadDivGraph("images/kakera_yuka.png", 10, 10, 1, 216, 216, effect_image[3]);
	LoadDivGraph("images/explosion.png", 9, 9, 1, 320, 320, explosion_image);
	LoadDivGraph("images/smoke.png", 9, 9, 1, 500, 500, smoke_image);
	pickaxe_image = LoadGraph("images/tsuruhashi.png");
}

void Stage::Update()
{
	for (int i = 0; i < treasure.size(); i++)
	{
		treasure[i].Update(this);  // 全要素に対するループ（宝物のアップデート）
		if (treasure[i].GetCanDelete())treasure.erase(treasure.begin() + i);
	}
	for (int i = 0; i < block.size(); i++)block[i].SetHitEcplosion(FALSE);
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

void Stage::HitBlastRange(int bom_num)
{
	if (bom[bom_num].GetCanDelete())
	{
		for (int i = 0; i < bom.size(); i++)
		{
			if (bom[bom_num].HitExplosion(&bom[i]))bom[i].SetCanDelete(TRUE);
		}
		for (int i = 0; i < treasure.size(); i++)
		{
			if ((bom[bom_num].HitExplosion(&treasure[i])) && (!treasure[i].GetOldHit(this, TRUE)))
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

	for (int i = 0; i < block.size(); i++)
	{
		if (bom[bom_num].HitExplosion(&block[i]))
		{
			BLOCK_TYPE block_type = block[i].GetBlockType();
			if ((block_type != BLOCK_TYPE::VERY_HARD_BLOCK) && (block_type != BLOCK_TYPE::NONE))
			{
				if (bom[bom_num].GetCanDelete())
				{
					int effect_image_type = 1;
					if (block_type == BLOCK_TYPE::HARD_BLOCK)effect_image_type = 2;
					else if (block_type == BLOCK_TYPE::GROUND_BLOCK)effect_image_type = 3;
					effect.emplace_back(block[i].GetLocation(), effect_image[effect_image_type], BREAK_BLOCK_IMAGE_NUM);
					block.erase(block.begin() + i);
					i--;
				}
				else block[i].SetHitEcplosion(TRUE);
			}
		}
	}
	if (bom[bom_num].GetCanDelete())
	{
		effect.emplace_back(bom[bom_num].GetLocation(), smoke_image, EXPLOSION_IMAGE_NUM);
		effect.emplace_back(bom[bom_num].GetLocation(), explosion_image, EXPLOSION_IMAGE_NUM);
		bom.erase(bom.begin() + bom_num);
	}
	else if (bom[bom_num].GetLocation().y > SCREEN_HEIGHT + 200)bom.erase(bom.begin() + bom_num);
}

void Stage::Draw1(float camera_work) const
{
	for (int i = 0; i < treasure.size(); i++) treasure[i].Draw(camera_work); // 全要素に対するループ(宝物の表示)
	for (int i = 0; i < block.size(); i++)block[i].Draw(camera_work);  // 全要素に対するループ（ブロックの表示）
}

void Stage::Draw2(float camera_work) const
{
	for (int i = 0; i < effect.size(); i++)effect[i].Draw(camera_work);
	for (int i = 0; i < bom.size(); i++)bom[i].Draw(camera_work);
	if (pickaxe != nullptr)pickaxe->Draw(camera_work);
}

HIT_STAGE Stage::HitStage(BoxCollider* bc)
{
	HIT_STAGE hit_stage = {FALSE, 0, BLOCK_TYPE::NONE};

	for (int i = 0; i < block.size(); i++)  // 全要素に対するループ
	{
		if (block[i].HitBox(bc))
		{
			if (block[i].GetBlockType() != BLOCK_TYPE::NONE)
			{
				hit_stage = { TRUE, i, block[i].GetBlockType() };
				break;
			}
		}
	}
	return hit_stage;
}

HIT_BOM Stage::HitBom(BoxCollider* bc)
{
	HIT_BOM hit_bom = { FALSE, 0 };
	for (int i = 0; i < bom.size(); i++)
	{
		if (bom[i].HitBox(bc))
		{
			hit_bom = { TRUE, i };
			break;
		}
	}
	return hit_bom;
}

HIT_TREASURE Stage::HitTreasure(BoxCollider* bc)
{
	HIT_TREASURE hit_treasure = { FALSE, 0, TREASURE_TYPE::KEY };
	for (int i = 0; i < treasure.size(); i++)
	{
		if (treasure[i].HitBox(bc))
		{
			hit_treasure = { TRUE, i, treasure[i].GetTreasureType() };
			break;
		}
	}
	return hit_treasure;
}

void Stage::DeleteTreasure(int num)
{
	treasure.erase(treasure.begin() + num);
}

bool Stage::HitPickaxe(BoxCollider* bc)
{
	for (int i = 0; i < bom.size(); i++)
	{
		if ((bom[i].HitBox(bc)) && (!bom[i].GetOldHit()))bom[i].SetCanDelete(TRUE);
	}

	for (int i = 0; i < treasure.size(); i++)
	{
		if (treasure[i].HitBox(bc))
		{
			if (!treasure[i].GetOldHit(this, FALSE))
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
	}

	for (int i = 0; i < block.size(); i++)  // 全要素に対するループ
	{
		if (block[i].HitBox(bc))
		{
			int block_type = static_cast<int>(block[i].GetBlockType());
			if ((block_type >= 1) && (block_type <= 4))//ブロックが土だったら
			{
				int effect_image_type = 1;
				if (block_type == 4)effect_image_type = 3;
				effect.emplace_back(block[i].GetLocation(), effect_image[effect_image_type], BREAK_BLOCK_IMAGE_NUM);
				block.erase(block.begin() + i);
				PlaySoundMem(break_block_se, DX_PLAYTYPE_BACK, TRUE);
				i--;
			}
			else if (block_type >= 5)return TRUE;//かたいブロックに当たったのでflgをTRUEにする
		}
	}
	return FALSE;
}

bool Stage::PutItem(BoxCollider* bc, ITEM_TYPE item_type)
{
	if (bc->GetLocation().y > SCREEN_HEIGHT)return FALSE;
	HIT_STAGE hit_stage = HitStage(bc);
	int block_type = static_cast<int>(hit_stage.block_type);

	if (item_type == ITEM_TYPE::PICKAXE)
	{
		if (hit_stage.flg)
		{
			if ((block_type > 0) && (block_type < 4))//ブロックが土だったら
			{
				if (--block_type == 0)
				{
					effect.emplace_back(block[hit_stage.num].GetLocation(), effect_image[1], BREAK_BLOCK_IMAGE_NUM);
					block.erase(block.begin() + hit_stage.num);
				}
				else
				{
					effect.emplace_back(block[hit_stage.num].GetLocation(), effect_image[0], BREAK_BLOCK_IMAGE_NUM);
					block[hit_stage.num].SetBlockType(block_type);

				}
			}
		}
	}
	else if (item_type == ITEM_TYPE::BLOCK)
	{
		if (!hit_stage.flg)
		{
			block.emplace_back(bc->GetLocation(), 4);
			if (!(HitTreasure(&block[block.size() - 1]).flg) && !(HitBom(&block[block.size() - 1]).flg))return TRUE;
			else block.erase(block.end() - 1);
		}
	}
	else
	{
		if (!hit_stage.flg)
		{
			block.emplace_back(bc->GetLocation(), 4);
			if (!(HitTreasure(&block[block.size() - 1]).flg) && !(HitBom(&block[block.size() - 1]).flg))
			{
				block.erase(block.end() - 1);
				bom.emplace_back(bc->GetLocation(), DATA{ 0,0 });
				return TRUE;
			}
			else block.erase(block.end() - 1);
		}
	}

	return FALSE;
}

void Stage::ThrowItem(DATA location, DATA speed, ITEM_TYPE item_type)
{
	if (item_type == ITEM_TYPE::PICKAXE)
	{
		if (pickaxe == nullptr)pickaxe = new Pickaxe(location, speed, pickaxe_image, hit_pickaxe_se);
		for (int i = 0; i < bom.size(); i++)bom[i].SetOldHit(FALSE);
		for (int i = 0; i < treasure.size(); i++)treasure[i].SetOldHit(FALSE);
	}
	else if (item_type == ITEM_TYPE::BLOCK)
	{

	}
	else
	{
		bom.emplace_back(location, speed);
	}
}

void Stage::Sway()
{
	for (int i = 0; i < block.size(); i++)  // 全要素に対するループ
	{
		if (GetRand(1000) == 0)
		{
			int block_type = static_cast<int>(block[i].GetBlockType());
			int effect_image_type = 0;
			if ((block_type >= 1) && (block_type <= 3))//ブロックが土だったら
			{
				if (block_type == 1)
				{
					effect_image_type = 1;
					effect.emplace_back(block[i].GetLocation(), effect_image[effect_image_type], BREAK_BLOCK_IMAGE_NUM);
					block.erase(block.begin() + i);
					i--;
				}
				else
				{
					effect.emplace_back(block[i].GetLocation(), effect_image[effect_image_type], BREAK_BLOCK_IMAGE_NUM);
					block[i].SetBlockType(block_type - 1);
				}
			}
		}
	}
}