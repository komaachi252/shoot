//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	処理[.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
#include "sprite.h"
#include "texture.h"
#include "collision.h"
#include "item.h"
#include <d3dx9.h>
#include "common.h"

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	定数定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	クラス宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
typedef struct Item_tag {
	Item_Type type;
	D3DXVECTOR2 position;
	bool is_used;
	int frame;
	Circle collision;
}Item;

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	プロトタイプ宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	グローバル変数宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
static int tex;

static const int TEX_ITEM_WIDTH = 256;
static const int TEX_ITEM_HEIGHT = 256;
static const float ITEM_WIDTH = 128.0f;
static const float ITEM_HEIGHT = 128.0f;
static const int FRAME_INTERVAL_DIVIDE = 10;
static const int STRAIGHT_TO_TURN = 140;   // フレーム
static const int TURN_TO_BACK = 160;   // フレーム
static const int TURN_ANGLE = 120;

static const float ITEM_RADIUS = 32.0f;
static const float ITEM_SPEED = 4.0f;


static Item* g_pItem;

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	初期化処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Item_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/item.png", TEX_ITEM_WIDTH, TEX_ITEM_HEIGHT);
	Texture_Load();

	g_pItem = new Item[ITEM_MAX];

	for (int i = 0; i < ITEM_MAX; i++) {
		(g_pItem + i)->is_used = false;
		(g_pItem + i)->collision.radius = ITEM_RADIUS;
		(g_pItem + i)->position.x = SCREEN_WIDTH;
	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	終了処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Item_Uninit(void)
{
	delete[] g_pItem;
	g_pItem = 0;
	Texture_Destroy(&tex, 1);
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	更新処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Item_Update(void)
{
	for (int i = 0; i < ITEM_MAX; i++) {
		if (!(g_pItem + i)->is_used) {
			continue;
		}
		(g_pItem + i)->position.x -= ITEM_SPEED;
		(g_pItem + i)->collision.position.x = (g_pItem + i)->position.x;
		(g_pItem + i)->collision.position.y = (g_pItem + i)->position.y;
		(g_pItem + i)->frame++;

		if ((g_pItem + i)->position.x < -ITEM_WIDTH * 0.5f) { (g_pItem + i)->is_used = false; }

	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	描画処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Item_Draw(void)
{
	float tx, ty;
	for (int i = 0; i < ITEM_MAX; i++) {
		if (!(g_pItem + i)->is_used) { continue; }
		tx = (g_pItem+ i)->position.x - (ITEM_WIDTH * 0.5f);
		ty = (g_pItem + i)->position.y - (ITEM_HEIGHT * 0.5f);
		Sprite_Draw(tex, tx, ty, ((g_pItem + i)->frame / FRAME_INTERVAL_DIVIDE % 2) * ITEM_WIDTH, ((g_pItem + i)->frame / FRAME_INTERVAL_DIVIDE / 2) * ITEM_HEIGHT, ITEM_WIDTH, ITEM_HEIGHT);
	}
}

void Item_Create(Item_Type type, float x, float y)
{
	int i;
	for (i = 0; i < ITEM_MAX; i++) {
		if ((g_pItem + i)->is_used) {
			continue;
		}
		break;
	}
	if (i >= ITEM_MAX) {
		return;
	}
	(g_pItem + i)->position.x = x;
	(g_pItem + i)->position.y = y;
	(g_pItem + i)->frame = 0;
	(g_pItem + i)->type = type;
	(g_pItem + i)->is_used = true;
	(g_pItem + i)->collision.position.x = x;
	(g_pItem + i)->collision.position.y = y;

}

bool is_used_Item(int index)
{
	return (g_pItem + index)->is_used;
}

void Item_Destroy(int index)
{
	(g_pItem + index)->position.x = SCREEN_WIDTH;
	(g_pItem + index)->position.y = SCREEN_HEIGHT;
	(g_pItem + index)->is_used = false;

}
Circle* Item_Get_Collision(int index) // 中身書き換えないアピールでコンストつける
{
	return &(g_pItem + index)->collision;
}

Item_Type Get_Item_Type(int index)
{
	return (g_pItem + index)->type;
}
