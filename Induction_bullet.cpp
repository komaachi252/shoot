//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	処理[.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
#include "collision.h"
#include "sprite.h"
#include "texture.h"
#include "player.h"
#include "system.h"
#include "Induction_bullet.h"
#include "patternanime.h"
#include "common.h"
#include "sound.h"

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	定数定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	クラス宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
enum Induction_Mode {
	NONE,
	GET_ANGLE,
	STRAIGHT
};

typedef struct Induction_Bullet_tag {
	float x;
	float y;
	Circle collision;
	Induction_Mode mode;
	bool is_used;
	bool is_turn_over;
	int angle;
	int frame;
}Induction_Bullet;

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	プロトタイプ宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	グローバル変数宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
static const int TEX_BULLET_WIDTH = 64;
static const int TEX_BULLET_HEIGHT = 32;

static const float BULLET_WIDTH = 32.0f;
static const float BULLET_HEIGHT = 32.0f;
static const float BULLET_RADIUS = BULLET_WIDTH * 0.5f;
static const float BULLET_SPEED = 7.0f;
static const int BULLET_FRAME_MAX = 2;
static const int BULLET_FRAME_DIVIDE = 12;
static const float INDUCTION_INTERVAL = 128.0f;
static int tex = 0;

static Induction_Bullet* g_pInduction_Bullet;

static float fsin[360] = {};
static float fcos[360] = {};
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	初期化処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Induction_Bullet_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/bullet4.png", TEX_BULLET_WIDTH, TEX_BULLET_HEIGHT);
	Texture_Load();
	
	g_pInduction_Bullet = new Induction_Bullet[INDUCTION_MAX];

	for (int i = 0; i < INDUCTION_MAX; i++) {
		(g_pInduction_Bullet + i)->is_used = false;
		(g_pInduction_Bullet + i)->is_turn_over = false;
		(g_pInduction_Bullet + i)->mode = NONE;
		(g_pInduction_Bullet + i)->collision.radius = BULLET_RADIUS;

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
void Induction_Bullet_Uninit(void)
{
	delete[] g_pInduction_Bullet;
	g_pInduction_Bullet = 0;
	Texture_Destroy(&tex, 1);
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	更新処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Induction_Bullet_Update(void)
{
	for (int i = 0; i < INDUCTION_MAX; i++) {
		if (!(g_pInduction_Bullet + i)->is_used) { continue; }

		if ((g_pInduction_Bullet + i)->mode == GET_ANGLE && !(g_pInduction_Bullet + i)->is_turn_over) {
			(g_pInduction_Bullet + i)->angle = GetAngle(get_player_pos_x(), get_player_pos_y(), (g_pInduction_Bullet + i)->x, (g_pInduction_Bullet + i)->y);
		}
		/*if ((g_pInduction_Bullet + i)->x > get_player_pos_x() + INDUCTION_INTERVAL && (g_pInduction_Bullet + i)->mode == GET_ANGLE) {
			(g_pInduction_Bullet + i)->mode = STRAIGHT;
		}*/
		if ((g_pInduction_Bullet + i)->x < get_player_pos_x() + INDUCTION_INTERVAL && (g_pInduction_Bullet + i)->mode == GET_ANGLE) {
			(g_pInduction_Bullet + i)->mode = STRAIGHT;
		}
		

		(g_pInduction_Bullet + i)->x += fcos[(g_pInduction_Bullet + i)->angle] * BULLET_SPEED;
		(g_pInduction_Bullet + i)->y -= fsin[(g_pInduction_Bullet + i)->angle] * BULLET_SPEED;

		(g_pInduction_Bullet + i)->collision.position.x = (g_pInduction_Bullet + i)->x;
		(g_pInduction_Bullet + i)->collision.position.y = (g_pInduction_Bullet + i)->y;

		(g_pInduction_Bullet + i)->frame++;
		if ((g_pInduction_Bullet + i)->x < -BULLET_WIDTH * 0.5f) {
			(g_pInduction_Bullet + i)->is_used = false;
		}
		if ((g_pInduction_Bullet + i)->x > SCREEN_WIDTH + BULLET_WIDTH * 0.5f) {
			(g_pInduction_Bullet + i)->is_used = false;
		}
		if ((g_pInduction_Bullet + i)->y < -BULLET_HEIGHT * 0.5f) {
			(g_pInduction_Bullet + i)->is_used = false;
		}
		if ((g_pInduction_Bullet + i)->y > SCREEN_HEIGHT + BULLET_HEIGHT * 0.5f) {
			(g_pInduction_Bullet + i)->is_used = false;
		}


	}
	//b.angle = GetAngle(get_player_pos_x(), get_player_pos_y(),b.x,b.y);

	//b.x -= fcos[b.angle] * BULLET_SPEED;
	//b.y += fsin[b.angle] * BULLET_SPEED;
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	描画処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Induction_Bullet_Draw(void)
{
	float tx, ty;

	for (int i = 0; i < INDUCTION_MAX; i++) {
		if (!(g_pInduction_Bullet + i)->is_used) { continue; }
		tx = (g_pInduction_Bullet + i)->x - (BULLET_WIDTH * 0.5f);
		ty = (g_pInduction_Bullet + i)->y - (BULLET_HEIGHT * 0.5f);
		Sprite_Draw(tex, tx, ty, ((g_pInduction_Bullet + i)->frame / BULLET_FRAME_DIVIDE % 2) * BULLET_WIDTH, 0.0f, BULLET_WIDTH, BULLET_HEIGHT);
	}



	//Sprite_Draw(tex, tx, ty, BULLET_WIDTH, BULLET_HEIGHT);
	//Sprite_Draw(tex, tx, ty, (b.frame / 6 % 2) * 128, (b.frame / 6 / 2) * 128, 128, 128);
	//Sprite_Draw(tex, tx, ty,((b.frame / 12) % 2) * 64, (b.frame / 12)  * 0, 64, 64);
	//PatternAnim_Draw(tex, tx, ty, 64, 64, 2, b.frame);
}

void Induction_Bullet_Create(float x, float y)
{

	int i;
	for (i = 0; i < INDUCTION_MAX; i++) {
		if ((g_pInduction_Bullet + i)->is_used) {
			continue;
		}
		break;
	}
	if (i >= INDUCTION_MAX) {
		return;
	}
	(g_pInduction_Bullet + i)->is_used = true;
	(g_pInduction_Bullet + i)->is_turn_over = false;
	(g_pInduction_Bullet + i)->x = x;
	(g_pInduction_Bullet + i)->y = y;
	(g_pInduction_Bullet + i)->collision.position.x = x;
	(g_pInduction_Bullet + i)->collision.position.y = y;
	(g_pInduction_Bullet + i)->mode = GET_ANGLE;
	(g_pInduction_Bullet + i)->angle = GetAngle(get_player_pos_x(), get_player_pos_y(), (g_pInduction_Bullet + i)->x, (g_pInduction_Bullet + i)->y);
	PlaySound(SOUND_LABEL_SE_INDUCTION_SHOT);
}

bool is_used_Induction_Bullet(int index)
{
	return (g_pInduction_Bullet + index)->is_used;
}

void Induction_Bullet_Destroy(int index)
{
	(g_pInduction_Bullet + index)->is_used = false;
}
Circle* Induction_Bullet_Get_Collision(int index) // 中身書き換えないアピールでコンストつける
{
	return &(g_pInduction_Bullet + index)->collision;
}

void Induction_Bullet_Turn_Over(int index)
{
	(g_pInduction_Bullet + index)->is_turn_over = true;
	(g_pInduction_Bullet + index)->angle = (g_pInduction_Bullet + index)->angle * -1.0f;
}
bool is_Induction_Turn_Over(int index)
{
	return (g_pInduction_Bullet + index)->is_turn_over;
}
