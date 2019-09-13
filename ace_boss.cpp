//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
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

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
#define RAYS_CREATE_MAX (8)
#define TRANS_MAX (5)

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
enum Ace_Mode {
	NONE,
	DEPARTURE,
	TRANSLATE,
	TURN_UP,
	TURN_DOWN,
	RAYS_CREATE,
	ATTACK,
	BREAK,
};

typedef struct Ace_Boss_tag {
	D3DXVECTOR2 position;
	bool is_used;
	bool is_collision;
	int hp;
	int angle;
	float enemy_y;
	int frame;
	Circle collision;
	Ace_Mode mode;
	int trans_item;
	int create_cnt;
	bool create_end;
}Ace_Boss;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static int tex = 0;

static const int TEX_ACE_WIDTH = 256;
static const int TEX_ACE_HEIGHT = 128;
static const float ACE_WIDTH = 256.0f;
static const float ACE_HEIGHT = 128.0f;
static const float ACE_RADIUS = 60.0f;

static const float ACE_SCALE = 0.75f;
static const float ACE_SPEED = 8.0f;
static const float DOWN_SPEED = 2.0f;
static const int DOWN_ANGLE = 120;
static const int BOMB_FRAME = 30;


static const float START_POS_X = SCREEN_WIDTH * 0.25f;
static const float START_POS_Y = - ACE_HEIGHT;
//static const float START_POS_X = 200.0f;
//static const float START_POS_Y = 200.0f;

static const float END_POS_X = 900.0f;
static const float END_POS_Y = SCREEN_HEIGHT * 0.5f;

static const float ENEMY_DISTANCE = 150.0f;
static const int CREATE_FRAME = 30;
static const int TRANS_FRAME = 150;

static const float MUZZLE_DISTANCE = -80.0f;
static Ace_Boss* g_pAce;

static const Ace_Mode g_AceModeTrans[TRANS_MAX] = { RAYS_CREATE, ATTACK, RAYS_CREATE, ATTACK, RAYS_CREATE };
//static const Ace_Mode g_AceModeTrans[TRANS_MAX] = { ATTACK, RAYS_CREATE, ATTACK, ATTACK, ATTACK };

static const float g_Rays_Create_Pos[RAYS_CREATE_MAX] = {150.0f, 360.0f, 580.0f, 460.0f, 140.0f, 360.0f, 440.0f, 150.0f };
//static const float g_Rays_Create_Pos[RAYS_CREATE_MAX] = {150.0f };
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Ace_Init(void)
{
	g_pAce = new Ace_Boss;
    tex = Texture_SetLoodFile("Asset/Texture/ace.png", TEX_ACE_WIDTH, TEX_ACE_HEIGHT);
	Texture_Load();
	g_pAce->is_used = false;
	g_pAce->collision.radius = ACE_RADIUS;
	g_pAce->hp = ACE_MAX_HP;
	g_pAce->trans_item = 0;
	g_pAce->create_cnt = 0;
	g_pAce->create_end = false;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Ace_Uninit(void)
{
	delete g_pAce;
	g_pAce = 0;
	Texture_Destroy(&tex, 1);
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Ace_Update(void)
{
	if (!g_pAce->is_used) { return; }
	g_pAce->frame++;
	switch (g_pAce->mode)
	{
	case NONE:
		break;
	case DEPARTURE:
		g_pAce->angle = GetAngle(g_pAce->position.x, g_pAce->position.y, END_POS_X, END_POS_Y);
		g_pAce->position.x -= Get_Cos(g_pAce->angle) * ACE_SPEED;
		g_pAce->position.y += Get_Sin(g_pAce->angle) * ACE_SPEED;
		if (g_pAce->position.x >= END_POS_X) {
			g_pAce->mode = TRANSLATE;
			g_pAce->frame = 0;
		}
		break;
	case TRANSLATE:
		if (g_pAce->frame >= TRANS_FRAME) {
			g_pAce->create_end = false;
			g_pAce->mode = g_AceModeTrans[g_pAce->trans_item];
			g_pAce->trans_item++;
			if (g_pAce->trans_item >= TRANS_MAX) {
				g_pAce->trans_item = 0;
			}
			g_pAce->frame = 0;
		}
		break;
	case RAYS_CREATE:
		if (g_pAce->frame >= CREATE_FRAME) {
			Rays_Create(SCREEN_WIDTH + Get_Rays_Width() * 0.5f, g_Rays_Create_Pos[g_pAce->create_cnt]);
			g_pAce->create_cnt++;
			g_pAce->frame = 0;
			if (g_pAce->create_cnt >= RAYS_CREATE_MAX) {
				g_pAce->create_cnt = 0;
				g_pAce->create_end = true;
				g_pAce->mode = TRANSLATE;
			}
		}
		break;
	case TURN_UP:
		if (g_pAce->enemy_y - g_pAce->position.y < ENEMY_DISTANCE ) {
			g_pAce->position.y -= ACE_SPEED;
		}else {
			if (!g_pAce->create_end) { g_pAce->mode = RAYS_CREATE; }
			else { g_pAce->mode = TRANSLATE; }
			//g_pAce->mode = RAYS_CREATE;
		}

		break;
	case TURN_DOWN:

		if (g_pAce->position.y - g_pAce->enemy_y < ENEMY_DISTANCE) {
			g_pAce->position.y += ACE_SPEED;
		}else {
			if (!g_pAce->create_end) { g_pAce->mode = RAYS_CREATE; }
			else { g_pAce->mode = TRANSLATE; }
		}
		break;
	case ATTACK:
		Enemy_Bullet_Create(g_pAce->position.x + MUZZLE_DISTANCE, g_pAce->position.y);
		g_pAce->mode = TRANSLATE;
		break;
	case BREAK:
		g_pAce->position.x -= Get_Cos(g_pAce->angle) * DOWN_SPEED;
		g_pAce->position.y += Get_Sin(g_pAce->angle) * DOWN_SPEED;

		//g_pAce->frame++;
		if (g_pAce->frame >= BOMB_FRAME) {
			Create_Explosion(g_pAce->position.x,g_pAce->position.y);
			g_pAce->frame = 0;
		}
		//setsceneResult
		break;
	default:
		break;
	}
	g_pAce->collision.position.x = g_pAce->position.x;
	g_pAce->collision.position.y = g_pAce->position.y;

	g_pAce->frame++;
	if (g_pAce->hp <= 0 && g_pAce->mode != BREAK) {
		g_pAce->mode = BREAK;
		g_pAce->angle = 120;
		g_pAce->frame = 0;
		g_pAce->is_collision = false;
		add_score(1000);
	}
	if (g_pAce->mode == BREAK && g_pAce->position.y >= SCREEN_HEIGHT + ACE_HEIGHT) {
		g_pAce->is_used = false;
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Ace_Draw(void)
{
	if (!g_pAce->is_used) { return; }
	float tx, ty;

	tx = g_pAce->position.x - (256 * 0.5f)* ACE_SCALE;
	ty = g_pAce->position.y - (128 * 0.5f)* ACE_SCALE;
	Sprite_Draw(tex, tx, ty, ACE_WIDTH * ACE_SCALE, ACE_HEIGHT * ACE_SCALE);

}

void Ace_Create(void)
{
	if (g_pAce->is_used) { return; }
	g_pAce->is_used = true;
	g_pAce->is_collision = true;
	g_pAce->position.x = START_POS_X;
	g_pAce->position.y = START_POS_Y;
	g_pAce->mode = DEPARTURE;

}

bool is_used_Ace(void)
{
	return g_pAce->is_used;
}

bool is_collision_Ace(void)
{
	return g_pAce->is_collision;
}

void Ace_Destroy(void)
{
	g_pAce->is_used = false;
}
Circle_tag* Ace_get_collision(void) // ’†g‘‚«Š·‚¦‚È‚¢ƒAƒs[ƒ‹‚ÅƒRƒ“ƒXƒg‚Â‚¯‚é
{
	return &g_pAce->collision;
}

void Ace_Turn(float y)
{
	if (g_pAce->mode == DEPARTURE || g_pAce->mode == TRANSLATE) {
		return;
	}
	g_pAce->enemy_y = y;
	if (y > SCREEN_HEIGHT * 0.5f) {
		g_pAce->mode = TURN_UP;
	}else {
		g_pAce->mode = TURN_DOWN;
	}
}

float Get_Ace_Pos_X(void)
{
	return g_pAce->position.x;
}

float Get_Ace_Pos_Y(void)
{
	return g_pAce->position.y;
}

void Ace_Sub_HP(Item_Type type) {
	if (type == METEOR) {
		g_pAce->hp -= METEOR_BULLET_DAMAGE;
	}else {
		g_pAce->hp -= NORMAL_BULLET_DAMAGE;
	}

}


void Ace_Break(void)
{

}
