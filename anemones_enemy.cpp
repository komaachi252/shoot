//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	エネミーANEMONES処理[anemone.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                                作成者 矢吹一俊
//                                                                作成日 
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
#include <d3dx9.h>
#include "collision.h"
#include "sprite.h"
#include "texture.h"
#include "common.h"
#include "enemy_bullet.h"
#include "anemones_enemy.h"
#include "Induction_bullet.h"

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	定数定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	クラス宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆

typedef struct Anemone_tag {
	D3DXVECTOR2 position;
	Circle collision;
	bool is_used;
	bool bullet_shoot;
	int frame;
}Anemone;

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	プロトタイプ宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	グローバル変数宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
static int tex;

static const int TEX_ANEMONES_WIDTH = 128;
static const int TEX_ANEMONES_HEIGHT = 64;
static const float ANEMONES_WIDTH = 128.0f;
static const float ANEMONES_HEIGHT = 64.0f;
static const int FRAME_INTERVAL_DIVIDE = 6;
static const int FRME_BULLET_TIME = 120; //フレーム

static const float ANEMONES_RADIUS = 32.0f;
static const float ANEMONES_SPEED = 4.0f;


static Anemone* g_pAnemones;

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	初期化処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Anemone_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/anemones.png", TEX_ANEMONES_WIDTH, TEX_ANEMONES_HEIGHT);
	Texture_Load();

	g_pAnemones = new Anemone[ANEMONES_MAX];

	for (int i = 0; i < ANEMONES_MAX; i++) {
		(g_pAnemones + i)->is_used = false;
		(g_pAnemones + i)->bullet_shoot = false;
		(g_pAnemones + i)->collision.radius = ANEMONES_RADIUS;

	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	終了処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Anemone_Uninit(void)
{
	delete[] g_pAnemones;
	Texture_Destroy(&tex,1);
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	更新処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Anemone_Update(void)
{
	for (int i = 0; i < ANEMONES_MAX; i++) {
		if (!(g_pAnemones + i)->is_used) { continue; }
		(g_pAnemones + i)->position.x -= ANEMONES_SPEED;

		(g_pAnemones + i)->frame++;
		if ((g_pAnemones + i)->frame >= FRME_BULLET_TIME && !(g_pAnemones + i)->bullet_shoot) {
			//弾
			Induction_Bullet_Create((g_pAnemones + i)->position.x, (g_pAnemones + i)->position.y - ANEMONES_HEIGHT * 0.5f);
			(g_pAnemones + i)->bullet_shoot = true;
		}
		(g_pAnemones + i)->collision.position.x = (g_pAnemones + i)->position.x;
		(g_pAnemones + i)->collision.position.y = (g_pAnemones + i)->position.y;
	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	描画処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Anemone_Draw(void)
{
	float tx, ty;
	for (int i = 0; i < ANEMONES_MAX; i++) {
		if (!(g_pAnemones + i)->is_used) { continue; }
		tx = (g_pAnemones + i)->position.x - (ANEMONES_WIDTH * 0.5f);
		ty = (g_pAnemones + i)->position.y - (ANEMONES_HEIGHT * 0.5f);
		Sprite_Draw(tex, tx, ty, ANEMONES_WIDTH, ANEMONES_HEIGHT);
	}
}

void Anemones_Create(float x, float y)
{
	int i;
	for (i = 0; i < ANEMONES_MAX; i++) {
		if ((g_pAnemones + i)->is_used) {
			continue;
		}
		break;
	}
	if (i >= ANEMONES_MAX) {
		return;
	}

	(g_pAnemones + i)->is_used = true;
	(g_pAnemones + i)->bullet_shoot = false;
	(g_pAnemones + i)->position.x = x;
	(g_pAnemones + i)->position.y = y;
	(g_pAnemones + i)->collision.position.x = x;
	(g_pAnemones + i)->collision.position.y = y;
	(g_pAnemones + i)->frame = 0;
}

bool is_used_Anemones(int index)
{
	return (g_pAnemones + index)->is_used;
}

void Anemones_Destroy(int index)
{
	(g_pAnemones + index)->is_used = false;
}
Circle* Anemones_Get_Collision(int index) // 中身書き換えないアピールでコンストつける
{
	return &(g_pAnemones + index)->collision;
}

float Get_Anemones_Pos_X(int index)
{
	return (g_pAnemones + index)->position.x;
}

float Get_Anemones_Pos_Y(int index)
{
	return (g_pAnemones + index)->position.y;
}