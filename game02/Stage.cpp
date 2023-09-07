#include"DxLib.h"
#include"Stage.h"

#define IMAGE_CHANGE_TIME 9

Stage::Stage(int stage_num, int stage_width)
{
	char stage_data[3][50] = { "data/stage/stage01.txt", "data/stage/stage02.txt","data/stage/stage03.txt" };
	char treasure_data[3][50] = { "data/stage/treasure01.txt", "data/stage/treasure02.txt","data/stage/treasure03.txt" };

	FILE* fp_s;//ステージ１ファイル読み込み
	FILE* fp_t;//アイテム１ファイル読み込み
	fopen_s(&fp_s, stage_data[stage_num], "r");
	fopen_s(&fp_t, treasure_data[stage_num], "r");

	for (int i = 0; i < STAGE_BLOCK_NUM_Y; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			int block_type, treasure_type;
			fscanf_s(fp_s, "%d", &block_type);
			fscanf_s(fp_t, "%d", &treasure_type);

			DATA location;
			location.x = ((j - 1) * BLOCK_SIZE_X) + (BLOCK_SIZE_X / 2);
			location.y = (i * BLOCK_SIZE_Y) + (BLOCK_SIZE_Y / 2);

			if (block_type != -1)block.emplace_back(location, block_type);
			if (treasure_type == 5) flag_location = location;
			else if (treasure_type != -1)treasure.emplace_back(location, treasure_type);
		}
	}
	fclose(fp_s);
	fclose(fp_t);

	break_block_se = LoadSoundMem("bgm/breakblock3.mp3");
	hit_pickaxe_se = LoadSoundMem("bgm/hitpickaxe2.mp3");
	LoadDivGraph("images/explosion.png", 10, 10, 1, 320, 320, explosion_image);
	LoadDivGraph("images/smoke.png", 10, 10, 1, 500, 500, smoke_image);
	pickaxe_image = LoadGraph("images/tsuruhashi.png");
	back_ground_image[0] = LoadGraph("images/background01.png");
	back_ground_image[1] = LoadGraph("images/background02.png");
	back_ground_image[2] = LoadGraph("images/background03.png");
	back_ground_image[3] = LoadGraph("images/background04.png");
	falling_block_image = LoadGraph("images/fallingblock.png");
	LoadDivGraph("images/kirakira.png", 4, 4, 1, 10, 10, kira_kira_image);
	LoadDivGraph("images/changeflag.png", 4, 4, 1, 36, 36, change_flag_image);

	int change_image_image[32];
	int count = 0;
	LoadDivGraph("images/changeblock.png", 32, 4, BLOCK_TYPE_NUM, 36, 36, change_image_image);
	for (int i = 0; i < BLOCK_TYPE_NUM; i++)
	{
		for (int j = 0; j < 4; j++)this->change_block_image[i][j] = change_image_image[count++];
	}

	int break_block_image[80];
	count = 0;
	LoadDivGraph("images/breakblock.png", 80, EFFECT_IMAGE_NUM, BLOCK_TYPE_NUM, 250, 250, break_block_image);
	for (int i = 0; i < BLOCK_TYPE_NUM; i++)
	{
		for (int j = 0; j < EFFECT_IMAGE_NUM; j++)this->break_block_image[i][j] = break_block_image[count++];
	}

	int break_treasure_image[50];
	count = 0;
	LoadDivGraph("images/breaktreasure.png", 50, EFFECT_IMAGE_NUM, TREASURE_TYPE_NUM, 250, 250, break_treasure_image);
	for (int i = 0; i < TREASURE_TYPE_NUM; i++)
	{
		for (int j = 0; j < EFFECT_IMAGE_NUM; j++)this->break_treasure_image[i][j] = break_treasure_image[count++];
	}

	for (int i = 0; i < KIRA_KIRA_NUM; i++)
	{
		kira_kira[i].location.y = 250 + GetRand(250);
		kira_kira[i].location.x = GetRand(SCREEN_WIDTH);
		kira_kira[i].size = (GetRand(4) + 1) / 5;
	}

	Init();
}

Stage::~Stage()
{
	block.clear();
	treasure.clear();
	effect.clear();
	bom.clear();
	fallingblock.clear();
	delete pickaxe;
}

void Stage::Init()
{
	flag = new Flag(flag_location);
	pickaxe = nullptr;
	image_change_time = IMAGE_CHANGE_TIME;
	image_type = 0;
	break_block_num = 0;
	fallingblock.clear();
}

void Stage::Update()
{
	break_block_num = 0;
	if (--image_change_time < 0)
	{
		if (++image_type > 3)image_type = 0;
		image_change_time = IMAGE_CHANGE_TIME;
		if(flag != nullptr)flag->SetFlagImage(change_flag_image[image_type]);
	}
	for (int i = 0; i < fallingblock.size(); i++)
	{
		fallingblock[i].Update();
		if (fallingblock[i].CanDelete())fallingblock.erase(fallingblock.begin() + i);
	}
	for (int i = 0; i < effect.size(); i++)
	{
		effect[i].Update();
		if (effect[i].CanDelete())effect.erase(effect.begin() + i);
	}
	for (int i = 0; i < treasure.size(); i++)
	{
		treasure[i].Update(this);
		if (treasure[i].GetCanDelete())treasure.erase(treasure.begin() + i);
	}
	for (int i = 0; i < block.size(); i++)
	{
		block[i].SetHitEcplosion(FALSE);
		if (image_change_time == 0)
		{
			int block_type = static_cast<int>(block[i].GetBlockType());
			if ((block_type == 1) || (block_type == 2) || (block_type == 3) || (block_type == 5))
			{
				block[i].SetBlockImage(change_block_image[block_type][image_type]);
			}
		}
	}
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
}

void Stage::HitBlastRange(int bom_num)
{
	if (bom[bom_num].GetCanDelete())
	{
		for (int i = 0; i < bom.size(); i++)if (bom[bom_num].HitExplosion(&bom[i]))bom[i].SetCanDelete(TRUE);
		for (int i = 0; i < treasure.size(); i++)
		{
			if ((bom[bom_num].HitExplosion(&treasure[i])) && (!HitBlock(&treasure[i]).flg))
			{
				if (treasure[i].GetTreasureType() == TREASURE_TYPE::BOM)bom.emplace_back(treasure[i].GetLocation(), DATA{ 0,0 });
				else effect.emplace_back(treasure[i].GetLocation(), break_treasure_image[static_cast<int>(treasure[i].GetTreasureType())]);
				treasure.erase(treasure.begin() + i);
				i--;
			}
		}
	}

	for (int i = 0; i < block.size(); i++)
	{
		if (bom[bom_num].HitExplosion(&block[i]))
		{
			int block_type = static_cast<int>(block[i].GetBlockType());
			if ((block_type != 7) && (block_type != 0))
			{
				if (bom[bom_num].GetCanDelete())
				{
					int image_type = block_type;
					if (block_type < 4)image_type = 1;
					effect.emplace_back(block[i].GetLocation(), break_block_image[image_type]);
					block.erase(block.begin() + i);
					i--;
				}
				else block[i].SetHitEcplosion(TRUE);
			}
		}
	}
	if (bom[bom_num].GetCanDelete())
	{
		effect.emplace_back(bom[bom_num].GetLocation(), smoke_image);
		effect.emplace_back(bom[bom_num].GetLocation(), explosion_image);
		bom.erase(bom.begin() + bom_num);
	}
	else if (bom[bom_num].GetLocation().y > SCREEN_HEIGHT + 200)bom.erase(bom.begin() + bom_num);
}

void Stage::Draw1(float camera_work) const
{
	DrawGraph(0, 0, back_ground_image[3], TRUE);
	for (int i = 0; i < KIRA_KIRA_NUM; i++)DrawRotaGraph(kira_kira[i].location.x, kira_kira[i].location.y, kira_kira[i].size, 0, kira_kira_image[image_type], TRUE);
	DrawGraph((camera_work / 10), 0, back_ground_image[2], TRUE);
	DrawGraph((camera_work / 7), 0, back_ground_image[1], TRUE);
	DrawGraph((camera_work / 5), 0, back_ground_image[0], TRUE);
	if(flag != nullptr)flag->Draw(camera_work);
	for (int i = 0; i < treasure.size(); i++) treasure[i].Draw(camera_work);
	for (int i = 0; i < block.size(); i++)block[i].Draw(camera_work);
}

void Stage::Draw2(float camera_work) const
{
	for (int i = 0; i < effect.size(); i++)effect[i].Draw(camera_work);
	for (int i = 0; i < bom.size(); i++)bom[i].Draw(camera_work);
	if (pickaxe != nullptr)pickaxe->Draw(camera_work);
	for (int i = 0; i < fallingblock.size(); i++)fallingblock[i].Draw(camera_work);
}

HIT_STAGE Stage::HitBlock(BoxCollider* bc)
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
	HIT_TREASURE hit_treasure = { FALSE, 0, TREASURE_TYPE::BOM };
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

bool Stage::HitFlag(BoxCollider* bc)
{
	if (flag != nullptr)
	{
		if (flag->HitBox(bc))
		{
			flag = nullptr;
			return TRUE;
		}
	}
	return FALSE;
}

void Stage::DeleteFlag()
{
	effect.emplace_back(flag->GetLocation(), break_treasure_image[0]);
	flag = nullptr;

}

void Stage::DeleteTreasure(int num)
{
	treasure.erase(treasure.begin() + num);
}

bool Stage::HitPickaxe(BoxCollider* bc)
{
	for (int i = 0; i < bom.size(); i++)if ((bom[i].HitBox(bc)) && (!bom[i].GetOldHit()))bom[i].SetCanDelete(TRUE);
	for (int i = 0; i < treasure.size(); i++)
	{
		if (treasure[i].HitBox(bc))
		{
			if (!treasure[i].GetOldHit(this))
			{
				if (treasure[i].GetTreasureType() == TREASURE_TYPE::BOM)
				{
					bom.emplace_back(treasure[i].GetLocation(), DATA{ 0,0 });
					bom[bom.size() - 1].SetOldHit(TRUE);
				}
				else effect.emplace_back(treasure[i].GetLocation(), break_treasure_image[static_cast<int>(treasure[i].GetTreasureType())]);
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
			if ((block_type > 0) && (block_type <= 5))//壊せるブロックなら
			{
				int image_type = block_type;
				if (block_type < 4)image_type = 1, break_block_num++;
				effect.emplace_back(block[i].GetLocation(), break_block_image[image_type]);
				block.erase(block.begin() + i);
				PlaySoundMem(break_block_se, DX_PLAYTYPE_BACK, TRUE);
				i--;
			}
			else if (block_type >= 5)return TRUE;//かたいブロックに当たったのでflgをTRUEにする
		}
	}
	return FALSE;
}

bool Stage::PutItem(BoxCollider* bc, ITEM_TYPE item_type, int item_num)
{
	if (bc->GetLocation().y > SCREEN_HEIGHT)return FALSE;
	if (item_type == ITEM_TYPE::PICKAXE)
	{
		if (pickaxe != nullptr)return FALSE;
	}
	else if (item_num == 0)return FALSE;

	HIT_STAGE hit_stage = HitBlock(bc);
	int block_type = static_cast<int>(hit_stage.block_type);

	if (item_type == ITEM_TYPE::PICKAXE)
	{
		if (hit_stage.flg)
		{
			if ((block_type > 0) && (block_type < 4))//ブロックが土だったら
			{
				effect.emplace_back(block[hit_stage.num].GetLocation(), break_block_image[block_type]);
				if (--block_type == 0)
				{
					block.erase(block.begin() + hit_stage.num);
					return TRUE;
				}
				else block[hit_stage.num].SetBlockType(block_type);
			}
		}
		else
		{
			HIT_BOM hit_bom = HitBom(bc);
			if (hit_bom.flg)bom[hit_bom.num].SetCanDelete(TRUE);
			HIT_TREASURE hit_treasure = HitTreasure(bc);
			if (hit_treasure.flg)
			{
				if (hit_treasure.treasure_type == TREASURE_TYPE::BOM)bom.emplace_back(treasure[hit_treasure.num].GetLocation(), DATA{ 0,0 });
				else effect.emplace_back(treasure[hit_treasure.num].GetLocation(), break_treasure_image[static_cast<int>(treasure[hit_treasure.num].GetTreasureType())]);
				treasure.erase(treasure.begin() + hit_treasure.num);
			}
		}
	}
	else if (item_type == ITEM_TYPE::BLOCK)
	{
		if (!hit_stage.flg)
		{
			if ((!HitTreasure(bc).flg) && (!HitBom(bc).flg))
			{
				block.emplace_back(bc->GetLocation(), 5);
				return TRUE;
			}
		}
	}
	else
	{
		if (!hit_stage.flg)
		{
			if ((!HitTreasure(bc).flg) && (!HitBom(bc).flg))
			{
				bom.emplace_back(bc->GetLocation(), DATA{ 0,0 });
				return TRUE;
			}
		}
	}
	return FALSE;
}

bool Stage::ThrowItem(DATA location, DATA speed, ITEM_TYPE item_type, int item_num)
{
	if (item_type == ITEM_TYPE::PICKAXE)
	{
		if (pickaxe == nullptr)pickaxe = new Pickaxe(location, speed, pickaxe_image, hit_pickaxe_se);
		for (int i = 0; i < bom.size(); i++)bom[i].SetOldHit(FALSE);
		for (int i = 0; i < treasure.size(); i++)treasure[i].SetOldHit(FALSE);
	}
	else if (item_type == ITEM_TYPE::BOM)
	{
		if (item_num != 0)
		{
			bom.emplace_back(location, speed);
			return TRUE;
		}
	}
	return FALSE;
}

bool Stage::GetPickaxeFlg()
{
	if (pickaxe == nullptr)return TRUE;
	else return FALSE;
}

void Stage::Sway()
{
	if (GetRand(10) == 0) fallingblock.emplace_back(falling_block_image);

	for (int i = 0; i < block.size(); i++)  // 全要素に対するループ
	{
		if (GetRand(1000) == 0)
		{
			int block_type = static_cast<int>(block[i].GetBlockType());
			if ((block_type > 0) && (block_type <= 3))//ブロックが土だったら
			{
				effect.emplace_back(block[i].GetLocation(), break_block_image[block_type]);
				if (block_type == 1)
				{
					block.erase(block.begin() + i);
					i--;
				}
				else block[i].SetBlockType(block_type - 1);
			}
		}
	}
}