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
#include "bullet.h"
#include "enemy_bullet.h"
#include "sound.h"
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static int tex = 0;

static const int TEX_BULLET_WIDTH = 64;
static const int TEX_BULLET_HEIGHT = 64;
static const float BULLET_WIDTH = 30.0f;
static const float BULLET_HEIGHT = 30.0f;


static const float BULLET_RADIUS = BULLET_WIDTH * 0.5f;
static const float BULLET_SPEED = 7.0f;

static Bullet* g_pEnemy_Bullet;
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Enemy_Bullet_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/bullet2.png", TEX_BULLET_WIDTH, TEX_BULLET_HEIGHT);
	Texture_Load();

	g_pEnemy_Bullet = new Bullet[ENEMY_BULLET_MAX];

	for (int i = 0; i < ENEMY_BULLET_MAX; i++) {
		(g_pEnemy_Bullet + i)->is_used = false;
		(g_pEnemy_Bullet + i)->is_turn_over = false;
		(g_pEnemy_Bullet + i)->collision.radius = BULLET_RADIUS;
	}

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Enemy_Bullet_Uninit(void)
{
	delete[] g_pEnemy_Bullet;
	g_pEnemy_Bullet = 0;
	Texture_Destroy(&tex, 1);

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Enemy_Bullet_Update(void)
{
	for (int i = 0; i < ENEMY_BULLET_MAX; i++) {
		if (!(g_pEnemy_Bullet + i)->is_used) {continue; }

		if (!(g_pEnemy_Bullet + i)->is_turn_over) {
			(g_pEnemy_Bullet + i)->x -= BULLET_SPEED;
		}
		else { (g_pEnemy_Bullet + i)->x += BULLET_SPEED; }
		
		(g_pEnemy_Bullet + i)->collision.position.x = (g_pEnemy_Bullet + i)->x;
		(g_pEnemy_Bullet + i)->collision.position.y = (g_pEnemy_Bullet + i)->y;
		if ((g_pEnemy_Bullet + i)->x < - BULLET_WIDTH * 0.5f) {
			(g_pEnemy_Bullet + i)->is_used = false;
		}
		if ((g_pEnemy_Bullet + i)->x > SCREEN_WIDTH + BULLET_WIDTH * 0.5f) {
			(g_pEnemy_Bullet + i)->is_used = false;
		}

	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Enemy_Bullet_Draw(void)
{
	float tx;
	float ty;

	for (int i = 0; i < ENEMY_BULLET_MAX; i++) {
		if (!(g_pEnemy_Bullet + i)->is_used) {
			continue;
		}
		tx = (g_pEnemy_Bullet + i)->x - (BULLET_WIDTH * 0.5f);
		ty = (g_pEnemy_Bullet + i)->y - (BULLET_HEIGHT * 0.5f);
		Sprite_Draw(tex, tx, ty, BULLET_WIDTH, BULLET_HEIGHT);
	}
}

void Enemy_Bullet_Create(float x, float y)
{
	int i;
	for (i = 0; i < ENEMY_BULLET_MAX; i++) {
		if ((g_pEnemy_Bullet + i)->is_used) {
			continue;
		}
		break;
	}
	(g_pEnemy_Bullet + i)->is_used = true;
	(g_pEnemy_Bullet + i)->is_turn_over = false;

	(g_pEnemy_Bullet + i)->x = x;
	(g_pEnemy_Bullet + i)->y = y;
	(g_pEnemy_Bullet + i)->collision.position.x = x;
	(g_pEnemy_Bullet + i)->collision.position.y = y;
	PlaySound(SOUND_LABEL_SE_ENEMY_SHOT);
}

bool is_used_Enemy_Bullet(int index)
{
	return (g_pEnemy_Bullet + index)->is_used;
}

void Enemy_Bullet_Destroy(int index)
{
	(g_pEnemy_Bullet + index)->is_used = false;
}
Circle* Enemy_Bullet_Get_Collision(int index) // ’†g‘‚«Š·‚¦‚È‚¢ƒAƒs[ƒ‹‚ÅƒRƒ“ƒXƒg‚Â‚¯‚é
{
	return &(g_pEnemy_Bullet + index)->collision;
}

void Enemy_Bullet_Turn_Over(int index)
{
	(g_pEnemy_Bullet + index)->is_turn_over = true;
}

bool is_Enemy_Turn_Over(int index)
{
	return (g_pEnemy_Bullet + index)->is_turn_over;
}
