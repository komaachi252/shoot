//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include <d3dx9.h>
#include "collision.h"
#include "sprite.h"
#include "texture.h"
#include "common.h"
#include "enemy_bullet.h"
#include "urchins_enemy.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
enum UrchinMode {
	NONE,
	STRAIGHT,
	TURN_UP,
	TURN_DOWN,
	BACK
};


typedef struct Urchin_tag {
	D3DXVECTOR2 position;
	float old_y;
	Circle collision;
	UrchinMode mode;
	bool is_used;
	bool bullet_shoot;
	int frame;
}Urchin;


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static int tex;

static const int TEX_URCHINS_WIDTH = 256;
static const int TEX_URCHINS_HEIGHT = 256;
static const float URCHINS_WIDTH = 128.0f;
static const float URCHINS_HEIGHT = 128.0f;
static const int FRAME_INTERVAL_DIVIDE = 6;
static const int STRAIGHT_TO_TURN = 140;   // ƒtƒŒ[ƒ€
static const int TURN_TO_BACK = 60;   // ƒtƒŒ[ƒ€
static const int TURN_ANGLE = 120;

static const float URCHINS_RADIUS = 64.0f;
static const float URCHINS_SPEED = 6.0f;
static const float URCHINS_DISTANCE = 128.0f;
static const int URCHINS_LEN = 5;
static Urchin* g_pUrchins;
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Urchins_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/urchins.png", TEX_URCHINS_WIDTH, TEX_URCHINS_HEIGHT);
	Texture_Load();

	g_pUrchins = new Urchin[URCHINS_MAX];

	for (int i = 0; i < URCHINS_MAX; i++) {
		(g_pUrchins + i)->is_used = false;
		(g_pUrchins + i)->bullet_shoot = false;
		(g_pUrchins + i)->collision.radius = URCHINS_RADIUS;
		(g_pUrchins + i)->mode = NONE;

	}

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Urchins_Uninit(void)
{
	delete[] g_pUrchins;
	g_pUrchins = 0;
	Texture_Destroy(&tex, 1);
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Urchins_Update(void)
{
	for (int i = 0; i < URCHINS_MAX; i++) {
		if (!(g_pUrchins + i)->is_used) { continue; }
		switch ((g_pUrchins + i)->mode)
		{
		case NONE:
			break;
		case STRAIGHT:
			(g_pUrchins + i)->position.x -= URCHINS_SPEED;
			break;
		case TURN_UP:
			(g_pUrchins + i)->position.x -= (float)cos(-TURN_ANGLE * D3DX_PI / 180) * URCHINS_SPEED;
			(g_pUrchins + i)->position.y += (float)sin(-TURN_ANGLE * D3DX_PI / 180) * URCHINS_SPEED;
			break;
		case TURN_DOWN:
			(g_pUrchins + i)->position.x -= (float)cos(TURN_ANGLE * D3DX_PI / 180) * URCHINS_SPEED;
			(g_pUrchins + i)->position.y += (float)sin(TURN_ANGLE * D3DX_PI / 180) * URCHINS_SPEED;
			break;
		case BACK:
			if (!(g_pUrchins + i)->bullet_shoot) {
				Enemy_Bullet_Create((g_pUrchins + i)->position.x, (g_pUrchins + i)->position.y);
				(g_pUrchins + i)->bullet_shoot = true;
			}
			//’e”­ŽË
			(g_pUrchins + i)->position.x += URCHINS_SPEED;
			break;
		default:
			break;
		}

		(g_pUrchins + i)->collision.position.x = (g_pUrchins + i)->position.x;
		(g_pUrchins + i)->collision.position.y = (g_pUrchins + i)->position.y;
		(g_pUrchins + i)->frame++;
		if ((g_pUrchins + i)->position.x <= (SCREEN_WIDTH * 0.5f) && (g_pUrchins + i) ->position.y > (SCREEN_HEIGHT * 0.5f) && (g_pUrchins + i)->mode == STRAIGHT) { 
			(g_pUrchins + i)->old_y = (g_pUrchins + i)->position.y;
			(g_pUrchins + i)->mode = TURN_UP;
		}
		else if ((g_pUrchins + i)->position.x <= (SCREEN_WIDTH * 0.5f) && (g_pUrchins + i)->position.y <= (SCREEN_HEIGHT * 0.5f) && (g_pUrchins + i)->mode == STRAIGHT) {
			(g_pUrchins + i)->old_y = (g_pUrchins + i)->position.y;
			(g_pUrchins + i)->mode = TURN_DOWN;
		}
		if ((g_pUrchins + i)->mode == TURN_UP && (g_pUrchins + i)->position.y <= (g_pUrchins + i)->old_y - URCHINS_DISTANCE) {(g_pUrchins + i)->mode = BACK;}
		if ((g_pUrchins + i)->mode == TURN_DOWN && (g_pUrchins + i)->position.y >= (g_pUrchins + i)->old_y + URCHINS_DISTANCE) {(g_pUrchins + i)->mode = BACK;}

		if ((g_pUrchins + i)->mode == BACK && (g_pUrchins + i)->position.x >= SCREEN_WIDTH + (URCHINS_WIDTH * 0.5f)) {
			(g_pUrchins + i)->is_used = false;
		}
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Urchins_Draw(void)
{
	float tx, ty;
	for (int i = 0; i < URCHINS_MAX; i++) {
		if (!(g_pUrchins + i)->is_used) { continue; }
		tx = (g_pUrchins + i)->position.x - (URCHINS_WIDTH * 0.5f);
		ty = (g_pUrchins + i)->position.y - (URCHINS_HEIGHT * 0.5f);
		Sprite_Draw(tex, tx, ty, ((g_pUrchins + i)->frame / FRAME_INTERVAL_DIVIDE % 2) * URCHINS_WIDTH, ((g_pUrchins + i)->frame / FRAME_INTERVAL_DIVIDE / 2) * URCHINS_HEIGHT, URCHINS_WIDTH, URCHINS_HEIGHT);

	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
/*void Urchins_Create(float x, float y)
{
	int i;
	for (i = 0; i < URCHINS_MAX; i++) {
		if ((g_pUrchins + i)->is_used) {
			continue;
		}
		break;
	}
	if (i >= URCHINS_MAX) {
		return;
	}
	(g_pUrchins + i)->is_used = true;
	(g_pUrchins + i)->bullet_shoot = false;
	(g_pUrchins + i)->position.x = x;
	(g_pUrchins + i)->position.y = y;
	(g_pUrchins + i)->mode = STRAIGHT;
	(g_pUrchins + i)->frame = 0;
}*/

void Urchins_Create(float x, float y)
{
	int create_cnt = 0;
	for (int i = 0; i < URCHINS_MAX; i++) {
		if ((g_pUrchins + i)->is_used) {
			continue;
		}
		(g_pUrchins + i)->is_used = true;
		(g_pUrchins + i)->bullet_shoot = false;
		(g_pUrchins + i)->position.x = x + (URCHINS_WIDTH * create_cnt);
		(g_pUrchins + i)->position.y = y;
		(g_pUrchins + i)->collision.position.x = (g_pUrchins + i)->position.x;
		(g_pUrchins + i)->collision.position.y = y;

		(g_pUrchins + i)->mode = STRAIGHT;
		(g_pUrchins + i)->frame = 0;
		create_cnt++;
		if (create_cnt >= URCHINS_LEN) {
			break;
		}
	}
}


bool is_used_Urchins(int index)
{
	return (g_pUrchins + index)->is_used;
}

void Urchins_Destroy(int index)
{
	(g_pUrchins + index)->is_used = false;
}
Circle* Urchins_Get_Collision(int index) // ’†g‘‚«Š·‚¦‚È‚¢ƒAƒs[ƒ‹‚ÅƒRƒ“ƒXƒg‚Â‚¯‚é
{
	return &(g_pUrchins + index)->collision;
}

float Get_Urchins_Pos_X(int index)
{
	return (g_pUrchins + index)->position.x;
}

float Get_Urchins_Pos_Y(int index)
{
	return (g_pUrchins + index)->position.y;
}
