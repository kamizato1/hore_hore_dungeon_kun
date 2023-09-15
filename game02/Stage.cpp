#define _USE_MATH_DEFINES
#include <math.h>
#include"DxLib.h"
#include"Stage.h"

#define IMAGE_CHANGE_TIME 9

Stage::Stage(int stage_num, int stage_width)
{
	LoadImages();

	char stage_data[STAGE_NUM][50] = { "data/stage/stage01.txt", "data/stage/stage02.txt","data/stage/stage03.txt" ,"data/stage/stage04.txt" ,"data/stage/stage05.txt" };
	char treasure_data[STAGE_NUM][50] = { "data/stage/treasure01.txt", "data/stage/treasure02.txt","data/stage/treasure03.txt" , "data/stage/treasure04.txt","data/stage/treasure05.txt" };

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
			else if ((treasure_type != -1) && treasure_type != 0)treasure.emplace_back(location, treasure_type);
		}
	}
	fclose(fp_s);
	fclose(fp_t);

	Init();
}

void Stage::LoadImages()
{
	explosion_se = LoadSoundMem("bgm/ExplosionSE.mp3");
	break_block_se = LoadSoundMem("bgm/breakblock3.mp3");
	hit_pickaxe_se = LoadSoundMem("bgm/hitpickaxe2.mp3");
	throw_pickaxe_se = LoadSoundMem("bgm/PickaxeThrow.mp3");
	break_pickaxe_se = LoadSoundMem("bgm/breakpickaxe.mp3");
	put_item_se = LoadSoundMem("bgm/stamp.mp3");

	//ブロック画像
	LoadDivGraph("images/block.png", 32, 4, BLOCK_TYPE_NUM, 36, 36, set_block_image);
	int count = 0;
	for (int i = 0; i < BLOCK_TYPE_NUM; i++)
	{
		for (int j = 0; j < 4; j++)block_image[i][j] = set_block_image[count++];
	}
	block_warning_image = LoadGraph("images/warning.png");

	//爆弾画像
	bom_image = LoadGraph("images/Bom/bom.png");
	bom_frame_image = LoadGraph("images/Bom/frame.png");
	LoadDivGraph("images/Bom/number.png", 6, 6, 1, 14, 23, bom_number_image);

	//宝画像
	LoadDivGraph("images/Treasure/treasure.png", TREASURE_TYPE_NUM, TREASURE_TYPE_NUM, 1, 36, 36, treasure_image);

	//旗画像
	LoadDivGraph("images/Flag/flag.png", 4, 4, 1, 36, 36, flag_image);


	LoadDivGraph("images/explosion.png", 10, 10, 1, 320, 320, explosion_image);
	LoadDivGraph("images/smoke.png", 10, 10, 1, 500, 500, smoke_image);
	pickaxe_image = LoadGraph("images/tsuruhashi.png");
	back_ground_image[0] = LoadGraph("images/background01.png");
	back_ground_image[1] = LoadGraph("images/background02.png");
	back_ground_image[2] = LoadGraph("images/background03.png");
	back_ground_image[3] = LoadGraph("images/background04.png");
	falling_block_image = LoadGraph("images/fallingblock.png");
	LoadDivGraph("images/kirakira.png", 4, 4, 1, 10, 10, kira_kira_image);
	

	count = 0;
	LoadDivGraph("images/breakblock.png", 80, EFFECT_IMAGE_NUM, BLOCK_TYPE_NUM, 250, 250, set_break_block_image);
	for (int i = 0; i < BLOCK_TYPE_NUM; i++)
	{
		for (int j = 0; j < EFFECT_IMAGE_NUM; j++)this->break_block_image[i][j] = set_break_block_image[count++];
	}

	count = 0;
	LoadDivGraph("images/breaktreasure.png", 50, EFFECT_IMAGE_NUM, TREASURE_TYPE_NUM, 250, 250, set_break_treasure_image);
	for (int i = 0; i < TREASURE_TYPE_NUM; i++)
	{
		for (int j = 0; j < EFFECT_IMAGE_NUM; j++)this->break_treasure_image[i][j] = set_break_treasure_image[count++];
	}

	for (int i = 0; i < KIRA_KIRA_NUM; i++)
	{
		kira_kira[i].location.y = 250 + GetRand(250);
		kira_kira[i].location.x = GetRand(SCREEN_WIDTH);
		kira_kira[i].size = (GetRand(4) + 1) / 5;
	}
}

void Stage::Delete()
{
	DeleteSoundMem(hit_pickaxe_se);
	DeleteSoundMem(break_block_se);
	DeleteSoundMem(explosion_se);
	DeleteSoundMem(throw_pickaxe_se);
	DeleteSoundMem(break_pickaxe_se);
	DeleteSoundMem(put_item_se);

	//ブロック画像
	for (int i = 0; i < 32; i++)DeleteGraph(set_block_image[i]);
	for (int i = 0; i < BLOCK_TYPE_NUM; i++)
	{
		for (int j = 0; j < 4; j++)DeleteGraph(block_image[i][j]);
	}
	DeleteGraph(block_warning_image);

	//爆弾画像
	DeleteGraph(bom_frame_image);
	DeleteGraph(bom_image);
	for (int i = 0; i < 6; i++)DeleteGraph(bom_number_image[i]);

	//宝画像
	for (int i = 0; i < TREASURE_TYPE_NUM; i++)DeleteGraph(treasure_image[i]);

	DeleteGraph(falling_block_image);
	for (int i = 0; i < 4; i++)DeleteGraph(back_ground_image[i]);

	for (int i = 0; i < 80; i++)DeleteGraph(set_break_block_image[i]);
	for (int i = 0; i < 50; i++)DeleteGraph(set_break_treasure_image[i]);
	

	for (int i = 0; i < BLOCK_TYPE_NUM; i++)
	{
		for (int j = 0; j < EFFECT_IMAGE_NUM; j++)
		{
			DeleteGraph(break_block_image[i][j]);
			DeleteGraph(explosion_image[j]);
			DeleteGraph(smoke_image[i]);
		}
	}

	for (int i = 0; i < TREASURE_TYPE_NUM; i++)
	{
		for (int j = 0; j < EFFECT_IMAGE_NUM; j++)DeleteGraph(break_treasure_image[i][j]);
	}

	for (int i = 0; i < BLOCK_TYPE_NUM; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			DeleteGraph(kira_kira_image[j]);
		}
	}
	DeleteGraph(pickaxe_image);

	block.clear();
	block.shrink_to_fit();

	treasure.clear();
	treasure.shrink_to_fit();

	for (int i = 0; i < effect.size(); i++)effect[i].Delete();
	effect.clear();
	effect.shrink_to_fit();

	bom.clear();
	bom.shrink_to_fit();

	for (int i = 0; i < fallingblock.size(); i++)fallingblock[i].Delete();
	fallingblock.clear();
	fallingblock.shrink_to_fit();

	delete pickaxe;
	//delete flag;
}

void Stage::Init()
{
	flag = new Flag(flag_location);
	delete pickaxe;
	pickaxe = nullptr;
	image_change_time = IMAGE_CHANGE_TIME;
	image_type = 0;
	break_block_num = 0;

	fallingblock.clear();
	effect.clear();
	bom.clear();
}

void Stage::Update()
{
	break_block_num = 0;
	if (--image_change_time < 0)
	{
		if (++image_type > 3)image_type = 0;
		image_change_time = IMAGE_CHANGE_TIME;
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

	for (int i = 0; i < block.size(); i++)block[i].SetHitEcplosion(FALSE);
	
	for (int i = 0; i < bom.size(); i++)
	{
		bom[i].Update(this);
		HitBlastRange(i);
	}
	if (pickaxe != nullptr)
	{
		pickaxe->Update(this);
		if (pickaxe->GetCanDelete())
		{
			effect.emplace_back(pickaxe->GetLocation(), break_block_image[0]);
			delete pickaxe;
			pickaxe = nullptr;
		}
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
				PlaySoundMem(break_pickaxe_se, DX_PLAYTYPE_BACK, TRUE);
				effect.emplace_back(treasure[i].GetLocation(), break_treasure_image[static_cast<int>(treasure[i].GetTreasureType())]);
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
		PlaySoundMem(explosion_se, DX_PLAYTYPE_BACK, TRUE);
	}
	else if (bom[bom_num].GetLocation().y > SCREEN_HEIGHT + 200)bom.erase(bom.begin() + bom_num);
}

void Stage::Draw1(float camera_work) const
{
	DrawGraph(0, 0, back_ground_image[3], TRUE);
	for (int i = 0; i < KIRA_KIRA_NUM; i++)DrawRotaGraph(kira_kira[i].location.x, kira_kira[i].location.y, kira_kira[i].size, 0, kira_kira_image[image_type], TRUE);
	DrawGraph((camera_work / 10), 0, back_ground_image[2], TRUE);
	DrawGraph((camera_work / 7), 0, back_ground_image[1], TRUE);
	for (int i = 0; i < fallingblock.size(); i++)if(fallingblock[i].GetSize() < 0.5)fallingblock[i].Draw(camera_work);
	DrawGraph((camera_work / 5), 0, back_ground_image[0], TRUE);
	if (flag != nullptr)DrawRotaGraph(flag->GetLocation().x + camera_work, flag->GetLocation().y, 1, 0, flag_image[image_type], TRUE);
	for (int i = 0; i < treasure.size(); i++)
	{
		DrawRotaGraph(treasure[i].GetLocation().x + camera_work, treasure[i].GetLocation().y, 1, 0, treasure_image[static_cast<int>(treasure[i].GetTreasureType())], TRUE);
	}
	for (int i = 0; i < block.size(); i++)//ブロック表示
	{
		GET_DRAW_BLOCK gdb = block[i].GetDrawBlock();
		if (gdb.block_type != 0)
		{
			DrawRotaGraph(gdb.location.x + camera_work, gdb.location.y, 1, 0, block_image[gdb.block_type][image_type], TRUE);
			if(gdb.hit_explosion)DrawRotaGraph(gdb.location.x + camera_work, gdb.location.y, 1, 0, block_warning_image, TRUE);
		}
	}
}

void Stage::Draw2(float camera_work) const
{
	for (int i = 0; i < effect.size(); i++)effect[i].Draw(camera_work);

	for (int i = 0; i < bom.size(); i++)//爆弾の表示
	{
		GET_DRAW_BOM gdb = bom[i].GetDrawBom();
		DrawRotaGraph(gdb.location.x + camera_work, gdb.location.y, 1, 0, bom_frame_image, TRUE);
		int count = gdb.count / FPS;
		DrawRotaGraph(gdb.location.x + camera_work, gdb.location.y, gdb.bom_size, ((M_PI / 180) * gdb.angle), bom_image, TRUE);
		if (!gdb.throw_flg)DrawRotaGraph((gdb.location.x - 2) + camera_work, gdb.location.y + 1, gdb.bom_size, 0, bom_number_image[count], TRUE);
	}

	if (pickaxe != nullptr)pickaxe->Draw(camera_work);
	for (int i = 0; i < fallingblock.size(); i++)if (fallingblock[i].GetSize() >= 0.5)fallingblock[i].Draw(camera_work);
}

HIT_STAGE Stage::HitBlock(BoxCollider* bc)
{
	HIT_STAGE hit_stage = {FALSE, 0, BLOCK_TYPE::NO_BLOCK, TRUE};

	for (int i = 0; i < block.size(); i++)  // 全要素に対するループ
	{
		if (block[i].HitBox(bc))
		{
			if (block[i].GetBlockType() == BLOCK_TYPE::NO_BLOCK)hit_stage.can_put = FALSE;
				else
				{
					hit_stage = { TRUE, i, block[i].GetBlockType() };
					break;
				}
		}
	}
	return hit_stage;
}

HIT_BOM Stage::HitBom(BoxCollider* bc, bool is_it_bom)
{
	HIT_BOM hit_bom = { FALSE, 0 };
	for (int i = 0; i < bom.size(); i++)
	{
		if (bom[i].HitBox(bc))
		{
			if (is_it_bom)
			{
				if ((bc->GetLocation().x != bom[i].GetLocation().x) || (bc->GetLocation().y != bom[i].GetLocation().y))
				{
					hit_bom = { TRUE, i };
					break;
				}
			}
			else
			{
				hit_bom = { TRUE, i };
				break;
			}
		}
	}
	return hit_bom;
}

HIT_TREASURE Stage::HitTreasure(BoxCollider* bc, bool is_it_treasure)
{
	HIT_TREASURE hit_treasure = { FALSE, 0, TREASURE_TYPE::COIN };
	for (int i = 0; i < treasure.size(); i++)
	{
		if (treasure[i].HitBox(bc))
		{
			if (is_it_treasure)
			{
				if ((bc->GetLocation().x != treasure[i].GetLocation().x) || (bc->GetLocation().y != treasure[i].GetLocation().y))
				{
					hit_treasure = { TRUE, i , treasure[i].GetTreasureType() };
					break;
				}
			}
			else
			{
				hit_treasure = { TRUE, i , treasure[i].GetTreasureType() };
				break;
			}
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
	for (int i = 0; i < bom.size(); i++)if (bom[i].HitBox(bc))bom[i].SetCanDelete(TRUE);
	for (int i = 0; i < treasure.size(); i++)
	{
		if (treasure[i].HitBox(bc))
		{
			if (!treasure[i].GetOldHit(this))
			{
				PlaySoundMem(break_pickaxe_se, DX_PLAYTYPE_BACK, TRUE);
				effect.emplace_back(treasure[i].GetLocation(), break_treasure_image[static_cast<int>(treasure[i].GetTreasureType())]);
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

bool Stage::PutItem(BoxCollider* bc, ITEM_TYPE item_type)
{
	if (bc->GetLocation().y > SCREEN_HEIGHT)return FALSE;

	HIT_STAGE hit_stage = HitBlock(bc);
	int block_type = static_cast<int>(hit_stage.block_type);

	if (item_type == ITEM_TYPE::PICKAXE)
	{
		if (hit_stage.flg)
		{
			if ((block_type > 0) && (block_type <= 4))//ブロックが土だったら
			{
				PlaySoundMem(break_block_se, DX_PLAYTYPE_BACK, TRUE);
				effect.emplace_back(block[hit_stage.num].GetLocation(), break_block_image[block_type]);
				if (block_type == 4) block.erase(block.begin() + hit_stage.num);
				else
				{
					if (--block_type == 0)
					{
						block.erase(block.begin() + hit_stage.num);
						return TRUE;
					}
					else block[hit_stage.num].SetBlockType(block_type);
				}
			}
			else PlaySoundMem(hit_pickaxe_se, DX_PLAYTYPE_BACK, TRUE);
		}
		else
		{
			HIT_BOM hit_bom = HitBom(bc, FALSE);
			if (hit_bom.flg)bom[hit_bom.num].SetCanDelete(TRUE);
			HIT_TREASURE hit_treasure = HitTreasure(bc, FALSE);
			if (hit_treasure.flg)
			{
				PlaySoundMem(break_pickaxe_se, DX_PLAYTYPE_BACK, TRUE);
				effect.emplace_back(treasure[hit_treasure.num].GetLocation(), break_treasure_image[static_cast<int>(treasure[hit_treasure.num].GetTreasureType())]);
				treasure.erase(treasure.begin() + hit_treasure.num);
			}
		}
	}
	else if (item_type == ITEM_TYPE::BLOCK)
	{
		if ((!hit_stage.flg) && (hit_stage.can_put))
		{
			if ((!HitTreasure(bc, FALSE).flg) && (!HitBom(bc, FALSE).flg))
			{
				block.emplace_back(bc->GetLocation(), 4);
				PlaySoundMem(put_item_se, DX_PLAYTYPE_BACK, TRUE);
				return TRUE;
			}
		}
	}
	else
	{
		if (!hit_stage.flg)
		{
			if ((!HitTreasure(bc, FALSE).flg) && (!HitBom(bc, FALSE).flg))
			{
				bom.emplace_back(bc->GetLocation(), DATA{ 0,0 });
				PlaySoundMem(put_item_se, DX_PLAYTYPE_BACK, TRUE);
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
		if (pickaxe == nullptr)pickaxe = new Pickaxe(location, speed, pickaxe_image, throw_pickaxe_se, hit_pickaxe_se, break_pickaxe_se);
		for (int i = 0; i < treasure.size(); i++)treasure[i].SetOldHit(FALSE);
	}
	else if (item_type == ITEM_TYPE::BOM)bom.emplace_back(location, speed);
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
			if ((block_type > 0) && (block_type <= 4))//ブロックが土だったら
			{
				effect.emplace_back(block[i].GetLocation(), break_block_image[block_type]);
				if ((block_type == 1) || (block_type == 4))
				{
					block.erase(block.begin() + i);
					i--;
				}
				else block[i].SetBlockType(block_type - 1);
			}
		}
	}
}


void Stage::Pause(bool flg)
{
	if (flg)
	{
		if (pickaxe != nullptr)pickaxe->Pause(TRUE);
	}
	else
	{
		if (pickaxe != nullptr)pickaxe->Pause(FALSE);
	}
}