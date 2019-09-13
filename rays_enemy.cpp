//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	処理[.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
#include <d3dx9.h>
#include "collision.h"
#include "sprite.h"
#include "texture.h"
#include "common.h"
#include "enemy_bullet.h"
#include "rays_enemy.h"
#include "system.h"
#include "player.h"

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	定数定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	クラス宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
enum Rays_Mode {
	NONE,
	STRAIGHT,
	GET_ANGLE,
	APPROACH
};

typedef struct Rays_tag {
	D3DXVECTOR2 position;
	Circle collision;
	Rays_Mode mode;
	bool is_used;
	int angle;
	int frame;
}Rays;

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	プロトタイプ宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	グローバル変数宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
static int tex = 0;

static const int TEX_RAYS_WIDTH = 256;
static const int TEX_RAYS_HEIGHT = 256;
static const float RAYS_WIDTH = 128.0f;
static const float RAYS_HEIGHT = 128.0f;
static const int FRAME_INTERVAL_DIVIDE = 6;
static const int STRAIGHT_TO_GET_ANGLE = 70;   // フレーム

static const float RAYS_RADIUS = 64.0f;
static const float RAYS_SPEED = 7.0f;

Rays* g_pRays;

static float fsin[360] = {};
static float fcos[360] = {};
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	初期化処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Rays_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/rays.png", TEX_RAYS_WIDTH, TEX_RAYS_HEIGHT);
	Texture_Load();

	g_pRays = new Rays[RAYS_MAX];

	for (int i = 0; i < RAYS_MAX; i++) {
		(g_pRays + i)->is_used = false;
		(g_pRays + i)->collision.radius = RAYS_RADIUS;
		(g_pRays + i)->mode = NONE;

	}
	//  サインコサインテーブル作成
	for (int i = 0; i<360; i++) {
		fsin[i] = (float)sin(i*D3DX_PI / 180);
		fcos[i] = (float)cos(i*D3DX_PI / 180);
	}

}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	終了処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Rays_Uninit(void)
{
	delete[] g_pRays;
	g_pRays = 0;
	Texture_Destroy(&tex, 1);

}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	更新処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Rays_Update(void)
{
	for (int i = 0; i < RAYS_MAX; i++) {
		if (!(g_pRays + i)->is_used) {
			continue;
		}
		switch ((g_pRays + i)->mode)
		{
		case NONE:
			break;
		case STRAIGHT:
			(g_pRays + i)->position.x -= RAYS_SPEED;
			break;
		case GET_ANGLE:
			(g_pRays + i)->angle = GetAngle((g_pRays + i)->position.x, (g_pRays + i)->position.y, get_player_pos_x(), get_player_pos_y());
			(g_pRays + i)->mode = APPROACH;
			break;
		case APPROACH:
			(g_pRays + i)->position.x -= fcos[(g_pRays + i)->angle] * RAYS_SPEED;
			(g_pRays + i)->position.y += fsin[(g_pRays + i)->angle] * RAYS_SPEED;
			break;
		default:
			break;
		}
		(g_pRays + i)->collision.position.x = (g_pRays + i)->position.x;
		(g_pRays + i)->collision.position.y = (g_pRays + i)->position.y;
		(g_pRays + i)->frame++;
		if ((g_pRays + i)->frame >= STRAIGHT_TO_GET_ANGLE && (g_pRays + i)->mode == STRAIGHT) { (g_pRays + i)->mode = GET_ANGLE; }
		if ((g_pRays + i)->position.x < -RAYS_WIDTH * 0.5f) { (g_pRays + i)->is_used = false; }
		if ((g_pRays + i)->position.y < -RAYS_HEIGHT * 0.5f) { (g_pRays + i)->is_used = false; }
		if ((g_pRays + i)->position.y > SCREEN_HEIGHT + RAYS_HEIGHT * 0.5f) { (g_pRays + i)->is_used = false; }

	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	描画処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Rays_Draw(void)
{
	float tx, ty;
	for (int i = 0; i < RAYS_MAX; i++) {
		if (!(g_pRays + i)->is_used) { continue; }
		tx = (g_pRays + i)->position.x - (RAYS_WIDTH * 0.5f);
		ty = (g_pRays + i)->position.y - (RAYS_HEIGHT * 0.5f);
		Sprite_Draw(tex, tx, ty, ((g_pRays + i)->frame / FRAME_INTERVAL_DIVIDE % 2) * RAYS_WIDTH, ((g_pRays + i)->frame / FRAME_INTERVAL_DIVIDE / 2) * RAYS_HEIGHT, RAYS_WIDTH, RAYS_HEIGHT);
	}
}

void Rays_Create(float x, float y)
{
	int i;
	for (i = 0; i < RAYS_MAX; i++) {
		if ((g_pRays + i)->is_used) {
			continue;
		}
		break;
	}
	(g_pRays + i)->is_used = true;
	(g_pRays + i)->position.x = x;
	(g_pRays + i)->position.y = y;
	(g_pRays + i)->collision.position.x = x;
	(g_pRays + i)->collision.position.y = y;
	(g_pRays + i)->mode = STRAIGHT;
	(g_pRays + i)->frame = 0;
}

bool is_used_Rays(int index)
{
	return (g_pRays + index)->is_used;
}

void Rays_Destroy(int index)
{
	(g_pRays + index)->is_used = false;
}
Circle* Rays_Get_Collision(int index) // 中身書き換えないアピールでコンストつける
{
	return &(g_pRays + index)->collision;
}

float Get_Rays_Pos_X(int index)
{
	return (g_pRays + index)->position.x;
}

float Get_Rays_Pos_Y(int index)
{
	return (g_pRays + index)->position.y;
}

int Get_Rays_Width(void)
{
	return (int)RAYS_WIDTH;
}