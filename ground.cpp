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
#include "collision.h"
#include "common.h"
#include <d3dx9.h>
#include "ground.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
enum Ground_Mode {
	NONE,
	START,
	HALF,
	END
};

typedef struct Ground_tag{
	D3DXVECTOR2 position;
	int cut_x;
	bool is_used;
	Square collision;
	Ground_Mode mode;
}Ground;


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static int tex = 0;

static const int TEX_GROUND_WIDTH = 2048;
static const int TEX_GROUND_HEIGHT = 35;
static const float GROUND_WIDTH = 1024.0f;
static const float GROUND_HEIGHT = 35.0f;

static const float GROUND_SPEED = 3.0f;

static const float HALF_TO_END = 1024.0f;

static const float SCALE = 3.0f;
static Ground* g_pGround;
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Ground_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/ground2.png", TEX_GROUND_WIDTH, TEX_GROUND_HEIGHT);
	Texture_Load();

	g_pGround = new Ground;
	g_pGround->is_used = false;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Ground_Uninit(void)
{
	delete g_pGround;
	Texture_Destroy(&tex,1);
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Ground_Update(void)
{
	if (g_pGround->is_used) {
		switch (g_pGround->mode)
		{
		case NONE:
			break;
		case START:
			g_pGround->position.x -= GROUND_SPEED;
			if (g_pGround->position.x <= SCREEN_WIDTH * 0.5f) { g_pGround->mode = HALF; }
			break;
		case HALF:
			g_pGround->cut_x += (int)GROUND_SPEED * 0.35f;
			if (g_pGround->cut_x >= HALF_TO_END) { g_pGround->mode = END; }
			break;
		case END:
			g_pGround->position.x -= GROUND_SPEED;
			if (g_pGround->position.x <= (-SCREEN_WIDTH * 0.5f )* SCALE) { 
				g_pGround->is_used = false;
			}
			break;
		default:
			break;
		}
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Ground_Draw(void)
{
	float tx, ty;
	if (g_pGround->is_used) {
		tx = g_pGround->position.x - GROUND_WIDTH * 0.5f;
		ty = g_pGround->position.y - GROUND_HEIGHT * 0.5f;
		Sprite_Draw(tex,tx, ty, g_pGround->cut_x,  0,GROUND_WIDTH, GROUND_HEIGHT, 0.0f, g_pGround->position.x, g_pGround->position.y, SCALE);
	}

}

void Ground_Create(void)
{
	if (g_pGround->is_used) {
		return;
	}
	g_pGround->is_used = true;
	g_pGround->position.x = SCREEN_WIDTH + (GROUND_WIDTH * 0.5f) * SCALE;
	g_pGround->position.y = SCREEN_HEIGHT - (GROUND_HEIGHT * 0.5f);
	g_pGround->mode = START;
	g_pGround->cut_x = 0;
}
