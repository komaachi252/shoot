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
#include <d3dx9.h>
#include "ace_boss.h"
#include "item.h"
#include "input.h"
#include "sound.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
typedef struct Boss_HP_tag {
	int logo_tex;
	int bar_tex;
	D3DXVECTOR2 position;
	bool is_used;
	float HP;
	int frame;
	int ace_hp;
}Boss_HP;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static const int TEX_LOGO_WIDTH = 150;
static const int TEX_LOGO_HEIGHT = 30;

static const float LOGO_WIDTH = 150.0f;
static const float LOGO_HEIGHT = 30.0f;
static const int TEX_BAR_WIDTH = 256;
static const int TEX_BAR_HEIGHT = 30;
static const float BAR_WIDTH = 270.0f;
static const float BAR_HEIGHT = 30.0f;

static const float LOGO_DISTANCE_X = LOGO_WIDTH * 0.5f + BAR_WIDTH * 0.5f;

static const float DAMAGE_1 = BAR_WIDTH / (float)ACE_MAX_HP;

static const float POS_X = SCREEN_WIDTH * 0.3f;

static const float POS_Y = 100.0f;

static const int END_FRAME = 360;

static Boss_HP* g_pBoss_HP;
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Boss_HP_Init(void)
{
	g_pBoss_HP = new Boss_HP;
	g_pBoss_HP->logo_tex = Texture_SetLoodFile("Asset/Texture/boss_hp.png", TEX_LOGO_WIDTH, TEX_LOGO_HEIGHT);
	g_pBoss_HP->bar_tex = Texture_SetLoodFile("Asset/Texture/hp_bar.png", TEX_LOGO_WIDTH, TEX_LOGO_HEIGHT);
	g_pBoss_HP->is_used = false;
	g_pBoss_HP->HP = BAR_WIDTH;
	g_pBoss_HP->position.x = POS_X;
	g_pBoss_HP->position.y = POS_Y;
	g_pBoss_HP->ace_hp = ACE_MAX_HP;
	g_pBoss_HP->frame = 0;
	Texture_Load();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Boss_HP_Uninit(void)
{
	Texture_Destroy(&g_pBoss_HP->logo_tex, 1);
	Texture_Destroy(&g_pBoss_HP->bar_tex, 1);
	delete g_pBoss_HP;
	g_pBoss_HP = 0;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Boss_HP_Update(void)
{
	if (!g_pBoss_HP->is_used) { return; }
	if (g_pBoss_HP->ace_hp <= 0) {
		g_pBoss_HP->frame++;
	}

	if (g_pBoss_HP->frame >= END_FRAME) {
		//SetScene(SCENE_RESULT);
	}


}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Boss_HP_Draw(void)
{
	if (!g_pBoss_HP->is_used) { return; }
	float tx = g_pBoss_HP->position.x - LOGO_WIDTH * 0.5f;
	float ty = g_pBoss_HP->position.y - LOGO_HEIGHT * 0.5f;
	Sprite_Draw(g_pBoss_HP->logo_tex, tx, ty, LOGO_WIDTH, LOGO_HEIGHT);
	tx = g_pBoss_HP->position.x - LOGO_WIDTH * 0.5f + LOGO_DISTANCE_X;
	Sprite_Draw(g_pBoss_HP->bar_tex, tx, ty, g_pBoss_HP->HP, BAR_HEIGHT);

}

void Boss_HP_Create(void)
{
	if (g_pBoss_HP->is_used) { return; }
	g_pBoss_HP->is_used = true;
	StopSound();
	PlaySound(SOUND_LABEL_BGM_BOSS);
}

void Sub_Boss_HP(Item_Type type)
{
	if (type == METEOR) {
		g_pBoss_HP->HP -= DAMAGE_1 * METEOR_BULLET_DAMAGE;
		g_pBoss_HP->ace_hp -= 2;
	}else {
		g_pBoss_HP->HP -= DAMAGE_1;
		g_pBoss_HP->ace_hp -= 1;
	}
}
