//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	bossˆ—[boss.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬Ò –îˆêr
//                                                               ì¬“ú 9/17(‰Î)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "sprite.h"
#include "texture.h"
#include "common.h"
#include "collision.h"
#include <d3dx9.h>
#include "player.h"
#include "system.h"
#include "ace_boss.h"
#include "item.h"
#include "fade.h"
#include "explosion.h"
#include "rays_enemy.h"
#include "enemy_bullet.h"
#include "score.h"
#include "Debug.h"
#include "boss_bullet.h"
#include "sound.h"
#include "cannon_bullet.h"
#include "scene.h"
#include "boss.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static const int TEX_BOSS_WIDTH = 512;
static const int TEX_BOSS_HEIGHT = 512;
static const float BOSS_WIDTH = 512.0f;
static const float BOSS_HEIGHT = 512.0f;

static const int TEX_HEAD_WIDTH = 512;
static const int TEX_HEAD_HEIGHT = 512;
static const float HEAD_WIDTH = 512.0f;
static const float HEAD_HEIGHT = 512.0f;
static const float HEAD_MUZZLE_Y = 128.0f;
static const float HEAD_MUZZLE_X = 128.0f;

static const float BOSS_RADIUS = 230.0f;
static const float BOSS_START_POS_X = SCREEN_WIDTH * 0.5f;
static const float BOSS_START_POS_Y = -BOSS_HEIGHT;
static const float BOSS_SPEED = 5.0f;

static const float BOSS_COLLISION_X = 80.0f;


static const float BOSS_TO_HEAD_POS_X = 80.0f;
static const float BOSS_TO_HEAD_POS_Y = -230.0f;

static const float BOSS_END_POS_X = SCREEN_WIDTH * 0.7f;
static const float BOSS_END_POS_Y = SCREEN_HEIGHT * 0.5f;

static const float BOSS_UP_LIMIT = 100.0f;
static const float BOSS_DOWN_LIMIT = SCREEN_HEIGHT + 28.0f;

static const int BOSS_WAIT_FRAME = 200;

static const int BOSS_BULLET_WAIT_FRAME = 120;

static const float CANNON_MUZZLE_DISTANCE_X = -190.0f;
static const float CANNON_MUZZLE_DISTANCE_Y = 0.0f;

static const float MUZZLE_WIDTH = 120.0f;
static const float MUZZLE_HEIGHT = 120.0f;

static const float MUZZLE_POS_X = -150.0f;
static const float MUZZLE_POS_Y = 0.0f;
static const int BOMB_FRAME = 20;

static const float DOWN_SPEED = 1.8f;
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
enum BOSS_MODE {
	BOSS_MODE_DEPARTURE,
	BOSS_MODE_WAIT,
	BOSS_MODE_MOVE_UP,
	BOSS_MODE_MOVE_DOWN,
	BOSS_MODE_BREAK,
	BOSS_MODE_MAX
};


typedef struct BOSS_tag {
	int tex;
	D3DXVECTOR2 position;
	Circle collision1;
	Square collision2;
	bool is_used;
	bool is_collision;
	int hp;
	int angle;
	BOSS_MODE mode;
	int frame;
	bool is_fade;
}BOSS;

typedef struct Head_tag {
	int tex;
	D3DXVECTOR2 position;
	Circle eyecollision;
	Circle collision2;
	Circle collision3;
	bool is_used;
	bool is_collision;
	int hp;
	float alpha;
	int frame;
}Head;


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static BOSS* g_pBoss;
static Head* g_pHead;
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Boss_Init(void)
{
	g_pBoss = new BOSS;
	g_pBoss->tex = Texture_SetLoodFile("Asset/Texture/oct.png", TEX_BOSS_WIDTH, TEX_BOSS_HEIGHT);
	g_pBoss->is_used = false;
	g_pBoss->is_collision = false;
	g_pBoss->is_fade = false;
	g_pBoss->position.x = BOSS_START_POS_X;
	g_pBoss->position.y = BOSS_START_POS_Y;
	g_pBoss->collision1.position.x = BOSS_START_POS_X + BOSS_COLLISION_X;
	g_pBoss->collision1.position.y = BOSS_START_POS_Y;
	g_pBoss->collision1.radius = BOSS_RADIUS;
	g_pBoss->mode = BOSS_MODE_DEPARTURE;
	g_pHead = new Head;
	g_pHead->tex = Texture_SetLoodFile("Asset/Texture/sea.png", TEX_HEAD_WIDTH, TEX_HEAD_HEIGHT);
	g_pHead->is_used = false;
	g_pHead->is_collision = false;
	Texture_Load();

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Boss_Uninit(void)
{
	Texture_Destroy(&g_pBoss->tex, 1);
	delete g_pBoss;
	Texture_Destroy(&g_pHead->tex, 1);
	delete g_pHead;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Boss_Update(void)
{
	if (!g_pBoss->is_used) {
		return;
	}
	switch (g_pBoss->mode)
	{
	case BOSS_MODE_DEPARTURE:
		g_pBoss->angle = GetAngle(g_pBoss->position.x, g_pBoss->position.y, BOSS_END_POS_X, BOSS_END_POS_Y);
		g_pBoss->position.x -= Get_Cos(g_pBoss->angle) * BOSS_SPEED;
		g_pBoss->position.y += Get_Sin(g_pBoss->angle) * BOSS_SPEED;
		if (g_pBoss->position.y >= BOSS_END_POS_Y && g_pBoss->position.x >= BOSS_END_POS_X) {
			g_pBoss->mode = BOSS_MODE_WAIT;
			g_pBoss->frame = 0;
		}
		break;

	case BOSS_MODE_WAIT:
		if (g_pBoss->frame >= BOSS_WAIT_FRAME) {
			if (g_pBoss->position.y >= SCREEN_HEIGHT * 0.6f) {
				Cannon_Bullet_Create(g_pBoss->position.x + CANNON_MUZZLE_DISTANCE_X, g_pBoss->position.y + CANNON_MUZZLE_DISTANCE_Y);
				g_pBoss->mode = BOSS_MODE_MOVE_UP;
			}else {
				Cannon_Bullet_Create(g_pBoss->position.x + CANNON_MUZZLE_DISTANCE_X, g_pBoss->position.y + CANNON_MUZZLE_DISTANCE_Y);
				g_pBoss->mode = BOSS_MODE_MOVE_DOWN;
			}
		}
		break;

	case BOSS_MODE_MOVE_UP:
		g_pBoss->position.y -= BOSS_SPEED;
		if (g_pBoss->position.y - (BOSS_HEIGHT * 0.5f) <= BOSS_UP_LIMIT) {
			g_pBoss->mode = BOSS_MODE_WAIT;
			Cannon_Bullet_Create(g_pBoss->position.x + CANNON_MUZZLE_DISTANCE_X, g_pBoss->position.y + CANNON_MUZZLE_DISTANCE_Y);
			g_pBoss->frame = 0;
		}
		break;
	case BOSS_MODE_MOVE_DOWN:
		g_pBoss->position.y += BOSS_SPEED;
		if (g_pBoss->position.y + (BOSS_HEIGHT * 0.5f) >= BOSS_DOWN_LIMIT) {
			g_pBoss->mode = BOSS_MODE_WAIT;
			Cannon_Bullet_Create(g_pBoss->position.x + CANNON_MUZZLE_DISTANCE_X, g_pBoss->position.y + CANNON_MUZZLE_DISTANCE_Y);
			g_pBoss->frame = 0;
		}
		break;
	case BOSS_MODE_BREAK:
		g_pBoss->position.y += DOWN_SPEED;
		if (g_pBoss->frame >= BOMB_FRAME) {
			Create_Explosion(g_pBoss->collision2.position.x - 50.0f, g_pBoss->collision2.position.y);
			Create_Explosion(g_pBoss->position.x + 120.0f, g_pBoss->position.y - 40.0f);
			Create_Explosion(g_pBoss->position.x + 70.0f, g_pBoss->position.y + 200.0f);
			Create_Explosion(g_pBoss->position.x + 200.0f, g_pBoss->position.y + 100.0f);
			Create_Explosion(g_pBoss->position.x -50.0f, g_pBoss->position.y - 200.0f);
			g_pBoss->frame = 0;
		}
		if (g_pBoss->position.y >= SCREEN_HEIGHT + BOSS_HEIGHT * 0.8f && !g_pBoss->is_fade) {
			Fade_Start(60,D3DCOLOR_RGBA(0,0,0,0),true);
			g_pBoss->is_fade = true;
		}
		break;
	default:
		break;
	}
	if (g_pBoss->is_fade && !Fade_IsFade()) {
		Scene_SetNextScene(SCENE_RESULT);
	}
	g_pBoss->collision1.position.x = g_pBoss->position.x + BOSS_COLLISION_X;
	g_pBoss->collision1.position.y = g_pBoss->position.y;
	g_pBoss->collision2.position.x = g_pBoss->position.x + MUZZLE_POS_X;
	g_pBoss->collision2.position.y = g_pBoss->position.y + MUZZLE_POS_Y;

	g_pBoss->frame++;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Boss_Draw(void)
{
	if (!g_pBoss->is_used) { return; }
	float tx, ty;
	tx = g_pBoss->position.x - (BOSS_WIDTH * 0.5f);
	ty = g_pBoss->position.y - (BOSS_HEIGHT * 0.5f);
	Sprite_Draw(g_pBoss->tex, tx, ty, BOSS_WIDTH, BOSS_HEIGHT);
	Debug_DrawCircle(g_pBoss->collision1.position.x, g_pBoss->collision1.position.y,g_pBoss->collision1.radius);
}

void Boss_Create(void)
{
	if (g_pBoss->is_used) { return; }
	StopSound(SOUND_LABEL_BGM_GAME);
	PlaySound(SOUND_LABEL_BGM_BOSS);
	g_pBoss->is_used = true;
	g_pBoss->is_collision = true;
	g_pBoss->is_fade = false;
	g_pBoss->hp = BOSS_HP_MAX;
	g_pBoss->mode = BOSS_MODE_DEPARTURE;
	g_pBoss->collision1.position.x = g_pBoss->position.x = BOSS_START_POS_X;
	g_pBoss->collision1.position.x += BOSS_COLLISION_X;
	g_pBoss->collision1.position.y = g_pBoss->position.y = BOSS_START_POS_Y;
	g_pBoss->collision2.width = MUZZLE_WIDTH;
	g_pBoss->collision2.height = MUZZLE_HEIGHT;
	g_pHead->is_used = true;
	g_pHead->is_collision = true;
	g_pHead->position.x = BOSS_START_POS_X + BOSS_TO_HEAD_POS_X;
	g_pHead->position.x = BOSS_START_POS_Y + BOSS_TO_HEAD_POS_Y;
	g_pBoss->angle = 0;
	g_pHead->alpha = 255;
}

bool Boss_Is_Used(void)
{
	return g_pBoss->is_used;
}

void Boss_Destroy(void)
{
	g_pBoss->is_used = false;
}

Circle* Boss_get_collision(void)
{
	return &g_pBoss->collision1;
}

Square* Boss_get_collision_square(void)
{
	return &g_pBoss->collision2;
}

float Boss_Get_Pos_X(void)
{
	return g_pBoss->position.x;
}

float Boss_Get_Pos_Y(void)
{
	return g_pBoss->position.y;
}

void Boss_Sub_HP(Item_Type type)
{
	if (type == METEOR) {
		g_pBoss->hp -= METEOR_BULLET_DAMAGE;
	}
	else {
		g_pBoss->hp -= NORMAL_BULLET_DAMAGE;
	}
	if (g_pBoss->hp <= 0) {
		g_pBoss->mode = BOSS_MODE_BREAK;
		g_pBoss->is_collision = false;
		g_pBoss->frame = 0;
	}

}
void Boss_Break(void)
{

}

bool Boss_Is_Collision(void)
{
	return g_pBoss->is_collision;
}

void Head_Update(void)
{
	if (!g_pHead->is_used) { return; }

	g_pHead->position.x = g_pBoss->position.x + BOSS_TO_HEAD_POS_X;
	g_pHead->position.y = g_pBoss->position.y + BOSS_TO_HEAD_POS_Y;
	if (g_pBoss->mode != BOSS_MODE_DEPARTURE) {
		if (g_pHead->frame >= BOSS_BULLET_WAIT_FRAME) {
			//Boss_Bullet_Create();
		}

	}
	g_pHead->frame++;
}

void Head_Draw(void)
{
	if (!g_pHead->is_used) { return; }
	float tx, ty;
	tx = g_pHead->position.x - (HEAD_WIDTH * 0.5f);
	ty = g_pHead->position.y - (HEAD_HEIGHT * 0.5f);
	Sprite_DrawAlpha(g_pHead->tex, tx, ty, HEAD_WIDTH, HEAD_HEIGHT, g_pHead->alpha);
}

bool Head_Is_Used(void)
{
	return g_pHead->is_used;
}

void Head_Destroy(void)
{
	g_pHead->is_used = false;
}

Circle* Head_Get_Collision1(void)
{
	return &g_pHead->eyecollision;
}

Circle* Head_Get_Collision2(void)
{
	return &g_pHead->collision2;
}


float Head_Get_Pos_X(void)
{
	return g_pHead->position.x;
}

float Head_Get_Pos_Y(void)
{
	return g_pHead->position.y;
}

void Head_Sub_HP(Item_Type type)
{
	if (type == METEOR) {
		g_pHead->hp -= METEOR_BULLET_DAMAGE;
	}
	else {
		g_pHead->hp -= NORMAL_BULLET_DAMAGE;
	}

}
void Head_Break(void)
{

}

bool Head_Is_Collision(void)
{
	return g_pHead->is_collision;
}