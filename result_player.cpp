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
#include <d3dx9.h>
#include "common.h"
#include "system.h"
#include "data.h"
#include "player.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
typedef struct Result_Player_tag {
	D3DXVECTOR2 position;
	float angle;
	bool is_stop;
}Result_Player;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static const int TEX_PLAYER_WIDTH = 256;
static const int TEX_PLAYER_HEIGHT = 128;
static const float PLAYER_WIDTH = 256.0f;
static const float PLAYER_HEIGHT = 128.0f;
static const float PLAYER_SPEED = 4.0f;

static const float END_POS_X = 1000.0f;
static const float END_POS_Y = SCREEN_HEIGHT * 0.5f;
static int tex = 0;

static Result_Player* g_pReplayer;
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Result_Player_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/player.png", TEX_PLAYER_WIDTH, TEX_PLAYER_HEIGHT);
	Texture_Load();
	g_pReplayer = new Result_Player;
	g_pReplayer->position = Get_Player_Pos();
	g_pReplayer->angle = GetAngle(g_pReplayer->position.x, g_pReplayer->position.y, END_POS_X, END_POS_Y);
	g_pReplayer->is_stop = false;

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Result_Player_Uninit(void)
{
	Texture_Destroy(&tex, 1);
	delete g_pReplayer;
	g_pReplayer = 0;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Result_Player_Update(void)
{
	if (!g_pReplayer->is_stop) {
		g_pReplayer->position.x -= Get_Cos(g_pReplayer->angle) * PLAYER_SPEED;
		g_pReplayer->position.y += Get_Sin(g_pReplayer->angle) * PLAYER_SPEED;
	}
	if (g_pReplayer->position.x >= END_POS_X) {
		g_pReplayer->is_stop = true;
	}


}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Result_Player_Draw(void)
{
	float tx = g_pReplayer->position.x - (PLAYER_WIDTH * 0.5f) * PLAYER_SCALE;
	float ty = g_pReplayer->position.y - (PLAYER_HEIGHT * 0.5f) * PLAYER_SCALE;
	Sprite_Draw(tex, tx, ty, PLAYER_WIDTH * PLAYER_SCALE, PLAYER_HEIGHT * PLAYER_SCALE);
}
