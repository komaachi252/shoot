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
#include "meteor_bullet.h"
#include "player.h"
#include "sound.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
typedef struct Meteor_tag {
	D3DXVECTOR2 position;
	bool is_used;
	Circle collision;
	int frame;
}Meteor;


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static const int TEX_BULLET_WIDTH = 128;
static const int TEX_BULLET_HEIGHT = 128;

static const float BULLET_WIDTH = 128.0f;
static const float BULLET_HEIGHT = 128.0f;

static const float BULLET_SPEED = 15.0f;

static const int BULLET_ANGLE = 120;

static int tex = 0;

static Meteor* g_pMeteor;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Meteor_Bullet_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/meteor.png", TEX_BULLET_WIDTH, TEX_BULLET_HEIGHT);
	Texture_Load();

	g_pMeteor = new Meteor[METEOR_BULLET_MAX];

	for (int i = 0; i < METEOR_BULLET_MAX; i++) {
		(g_pMeteor + i)->is_used = false;
		(g_pMeteor + i)->collision.radius = (BULLET_WIDTH * 0.5f);
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Meteor_Bullet_Uninit(void)
{
	delete[] g_pMeteor;
	g_pMeteor = 0;
	Texture_Destroy(&tex, 1);
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Meteor_Bullet_Update(void)
{
	for (int i = 0; i < METEOR_BULLET_MAX; i++) {
		if (!(g_pMeteor + i)->is_used) {
			continue;
		}
		(g_pMeteor + i)->position.x -= (float)cos(BULLET_ANGLE * D3DX_PI / 180) * BULLET_SPEED;
		(g_pMeteor + i)->position.y += (float)sin(BULLET_ANGLE * D3DX_PI / 180) * BULLET_SPEED;
		(g_pMeteor + i)->collision.position.x = (g_pMeteor + i)->position.x;
		(g_pMeteor + i)->collision.position.y = (g_pMeteor + i)->position.y;
		if ((g_pMeteor + i)->position.x >= SCREEN_WIDTH + BULLET_WIDTH * 0.5f) {
			(g_pMeteor + i)->is_used = false;
		}
		if ((g_pMeteor + i)->position.y >= SCREEN_HEIGHT + BULLET_HEIGHT * 0.5f) {
			(g_pMeteor + i)->is_used = false;
		}
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Meteor_Bullet_Draw(void)
{
	float tx, ty;
	for (int i = 0; i < METEOR_BULLET_MAX; i++) {
		if (!(g_pMeteor + i)->is_used) { continue; }
		tx = (g_pMeteor + i)->position.x - (BULLET_WIDTH * 0.5f);
		ty = (g_pMeteor + i)->position.y - (BULLET_HEIGHT * 0.5f);
		Sprite_Draw(tex, tx, ty, BULLET_WIDTH, BULLET_HEIGHT);
	}
}

void Meteor_Bullet_Create(float x, float y)
{
	int i;
	for (i = 0; i < METEOR_BULLET_MAX; i++) {
		if ((g_pMeteor + i)->is_used != false) {
			continue;
		}
		break;
	}
	if (i >= METEOR_BULLET_MAX) { return; }
	(g_pMeteor + i)->is_used = true;
	(g_pMeteor + i)->position.x = x;
	(g_pMeteor + i)->position.y = y;
	PlaySound(SOUND_LABEL_SE_METEOR_SHOT);
}

bool is_used_Meteor_Bullet(int index)
{
	return (g_pMeteor + index)->is_used;
}

void Meteor_Bullet_Destroy(int index)
{
	(g_pMeteor + index)->is_used = false;
}
Circle* Meteor_Bullet_get_collision(int index) // ’†g‘‚«Š·‚¦‚È‚¢ƒAƒs[ƒ‹‚ÅƒRƒ“ƒXƒg‚Â‚¯‚é
{
	return &(g_pMeteor + index)->collision;
}

float Get_Meteor_Height(void) 
{
	return BULLET_HEIGHT;
}