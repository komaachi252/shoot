//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[GameMaster.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "GameMaster.h"
#include "urchins_enemy.h"
#include "rays_enemy.h"
#include "anemones_enemy.h"
#include "ground.h"
#include "data.h"
#include "common.h"
#include "ace_boss.h"
#include "boss_hp.h"
#include "player.h"
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
#define ENEMY_POP_NUM 10

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
enum Enemy_type {
	URCHINS,
	RAYS,
	ANEMONES,
	ACE
};

typedef struct Game_Master_tag {
	Stage_Number stage_num;
	Game_Scene scene;
	int frame;
	int itr;
	Enemy_type create_type[ENEMY_POP_NUM];
}Game_Master;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static int frame[ENEMY_POP_NUM] = { 80, 120, 120, 120, 90, 60, 60, 60, 30, 80 };
static int frame2[ENEMY_POP_NUM] = { 120, 10, 20, 10, 10, 20, 20, 20, 20, 20 };
static int frame3[ENEMY_POP_NUM] = { 80, 60, 70, 60, 60, 70, 50, 60, 50, 60 };
static int frame4[ENEMY_POP_NUM] = { 20, 20, 10, 20, 30, 70, 30, 60, 30, 60 };
static float pop_y[ENEMY_POP_NUM] = { 200.0f, 600.0f, 200.0f, 600.0f, 300.0f, 100.0f, 500.0f, 200.0f, 200.0f, 400.0f };
static float pop_y2[ENEMY_POP_NUM] = { 200.0f, 600.0f, 200.0f, 600.0f, 400.0f, 150.0f, 580.0f, 200.0f, 400.0f, 150.0f };
static float pop_y3[ENEMY_POP_NUM] = { 100.0f, 150.0f, 300.0f, 450.0f, 200.0f, 150.0f, 580.0f, 200.0f, 300.0f, 400.0f };
static float pop_y4[ENEMY_POP_NUM] = { 300.0f, 150.0f, 250.0f, 400.0f, 550.0f, 150.0f, 580.0f, 200.0f, 150.0f, 450.0f };
static Enemy_type type[ENEMY_POP_NUM] = { URCHINS, URCHINS, URCHINS, URCHINS, RAYS, RAYS, RAYS, RAYS, URCHINS, URCHINS};
static Enemy_type type2[ENEMY_POP_NUM] = { URCHINS, URCHINS, ANEMONES, URCHINS, RAYS, ANEMONES, URCHINS, URCHINS, ANEMONES, RAYS};
static Enemy_type type3[ENEMY_POP_NUM] = { URCHINS, RAYS, URCHINS, RAYS, RAYS, URCHINS, RAYS, URCHINS, URCHINS, URCHINS };
static Enemy_type type4[ENEMY_POP_NUM] = { RAYS, URCHINS, RAYS, URCHINS, RAYS, URCHINS, RAYS, RAYS, URCHINS, URCHINS };

static const float ENEMY_HALF_WIDTH = 64.0f;
static const float ANEMONE_POS_Y = 660.0f;

static Game_Master* g_pGame_Master;
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Master_Init(void)
{
	g_pGame_Master = new Game_Master;
	g_pGame_Master->itr = 0;

	//ƒXƒe[ƒW”Ô†‚ðŽó‚¯Žæ‚é
	g_pGame_Master->stage_num = STAGE_1;
	g_pGame_Master->scene = SCENE_1;
	g_pGame_Master->frame = 0;
	switch (g_pGame_Master->stage_num)
	{
	case STAGE_1:
	break;
	case STAGE_2:
		break;
	case STAGE_3:
		break;
	default:
		break;
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Master_Uninit(void)
{
	delete g_pGame_Master;
	g_pGame_Master = 0;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Master_Update(void)
{
	if (!is_used_player()) { return; }
	switch (g_pGame_Master->stage_num)
	{
	case STAGE_1:
		switch (g_pGame_Master->scene)
		{
		case SCENE_NON:break;
		case SCENE_1:
			if (g_pGame_Master->frame >= frame[g_pGame_Master->itr]) {
				switch (type[g_pGame_Master->itr])
				{
				case URCHINS:
					Urchins_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y[g_pGame_Master->itr]);
					break;
				case RAYS:
					Rays_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y[g_pGame_Master->itr]);
					break;
				case ANEMONES:
					Anemones_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y[g_pGame_Master->itr]);
					break;
				default:
					break;
				}
				g_pGame_Master->itr++;
				g_pGame_Master->frame = 0;
				if (g_pGame_Master->itr >= ENEMY_POP_NUM) {
					g_pGame_Master->itr = 0;
					g_pGame_Master->scene = SCENE_2;
				}
			}
			break;
		case SCENE_2:
			if (g_pGame_Master->frame >= frame2[g_pGame_Master->itr]) {
				Rays_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y[g_pGame_Master->itr]);
				g_pGame_Master->itr++;
				g_pGame_Master->frame = 0;
				if (g_pGame_Master->itr >= ENEMY_POP_NUM) {
					g_pGame_Master->itr = 0;
					g_pGame_Master->scene = SCENE_3;
				}
			}
			break;
		case SCENE_3:
			if (g_pGame_Master->frame >= frame3[g_pGame_Master->itr]) {
				Urchins_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y2[g_pGame_Master->itr]);
				g_pGame_Master->itr++;
				g_pGame_Master->frame = 0;
				if (g_pGame_Master->itr >= ENEMY_POP_NUM) {
					g_pGame_Master->itr = 0;
					g_pGame_Master->scene = SCENE_4;
				}
			}
			break;
		case SCENE_4:
			Ground_Create();
			g_pGame_Master->scene = SCENE_5;
			break;
		case SCENE_5:
			if (g_pGame_Master->frame >= frame3[g_pGame_Master->itr]) {
				switch (type2[g_pGame_Master->itr])
				{
				case URCHINS:
					Urchins_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y3[g_pGame_Master->itr]);
					break;
				case RAYS:
					Rays_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y3[g_pGame_Master->itr]);
					break;
				case ANEMONES:
					Anemones_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, ANEMONE_POS_Y);
					break;
				default:
					break;
				}
				g_pGame_Master->itr++;
				g_pGame_Master->frame = 0;
				if (g_pGame_Master->itr >= ENEMY_POP_NUM) {
					g_pGame_Master->itr = 0;
					g_pGame_Master->scene = SCENE_6;
				}
			}
			break;
		case SCENE_6:
			if (g_pGame_Master->frame >= frame3[g_pGame_Master->itr]) {
				switch (type2[g_pGame_Master->itr])
				{
				case URCHINS:
					Urchins_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y3[g_pGame_Master->itr]);
					break;
				case RAYS:
					Rays_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y2[g_pGame_Master->itr]);
					break;
				case ANEMONES:
					Anemones_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, ANEMONE_POS_Y);
					break;
				default:
					break;
				}
				g_pGame_Master->itr++;
				g_pGame_Master->frame = 0;
				if (g_pGame_Master->itr >= ENEMY_POP_NUM) {
					g_pGame_Master->itr = 0;
					g_pGame_Master->scene = SCENE_7;
				}
			}
			break;
		case SCENE_7:
			if (g_pGame_Master->frame >= frame2[g_pGame_Master->itr]) {
				Rays_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y[g_pGame_Master->itr]);
				g_pGame_Master->itr++;
				g_pGame_Master->frame = 0;
				if (g_pGame_Master->itr >= ENEMY_POP_NUM) {
					g_pGame_Master->itr = 0;
					g_pGame_Master->scene = SCENE_DIS;
				}
			}
			break;
		case SCENE_DIS:
			Ground_Create();
			g_pGame_Master->scene = SCENE_8;
			break;
		case SCENE_8:
			if (g_pGame_Master->frame >= frame3[g_pGame_Master->itr]) {
				Urchins_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y2[g_pGame_Master->itr]);
				g_pGame_Master->itr++;
				g_pGame_Master->frame = 0;
				if (g_pGame_Master->itr >= ENEMY_POP_NUM) {
					g_pGame_Master->itr = 0;
					g_pGame_Master->scene = SCENE_9;
				}
			}
			break;
		case SCENE_9:
			if (g_pGame_Master->frame >= frame4[g_pGame_Master->itr]) {
				switch (type3[g_pGame_Master->itr])
				{
				case URCHINS:
					Urchins_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y3[g_pGame_Master->itr]);
					break;
				case RAYS:
					Rays_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y2[g_pGame_Master->itr]);
					break;
				case ANEMONES:
					Anemones_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, ANEMONE_POS_Y);
					break;
				default:
					break;
				}
				g_pGame_Master->itr++;
				g_pGame_Master->frame = 0;
				if (g_pGame_Master->itr >= ENEMY_POP_NUM) {
					g_pGame_Master->itr = 0;
					g_pGame_Master->scene = SCENE_10;
				}
			}
			break;
		case SCENE_10:
			if (g_pGame_Master->frame >= frame4[g_pGame_Master->itr]) {
				switch (type4[g_pGame_Master->itr])
				{
				case URCHINS:
					Urchins_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y4[g_pGame_Master->itr]);
					break;
				case RAYS:
					Rays_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, pop_y4[g_pGame_Master->itr]);
					break;
				case ANEMONES:
					Anemones_Create(SCREEN_WIDTH + ENEMY_HALF_WIDTH, ANEMONE_POS_Y);
					break;
				default:
					break;
				}
				g_pGame_Master->itr++;
				g_pGame_Master->frame = 0;
				if (g_pGame_Master->itr >= ENEMY_POP_NUM) {
					g_pGame_Master->itr = 0;
					g_pGame_Master->scene = SCENE_BOSS;
				}
			}
			break;
		case SCENE_BOSS:
			Ace_Create();
			Boss_HP_Create();
			g_pGame_Master->scene = SCENE_NON;
			break;
		default:
			break;
		}
		break;
	case STAGE_2:
		switch (g_pGame_Master->scene)
		{
		case SCENE_1:
			break;
		case SCENE_2:
			break;

		default:
			break;
		}
		break;
	case STAGE_3:
		switch (g_pGame_Master->scene)
		{
		case SCENE_1:
			break;
		case SCENE_2:
			break;

		default:
			break;
		}
		break;
	default:
		break;
	}
	g_pGame_Master->frame++;
}

