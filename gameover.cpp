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
#include "fade.h"
#include "input.h"
#include "sound.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
typedef struct GameOver_tag{
	D3DXVECTOR2 position;
	float is_used;
	int to_scene_frame;
}GameOver;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static const int TEX_GAME_OVER_WIDTH = 190;
static const int TEX_GAME_OVER_HEIGHT = 30;

static const int GAME_OVER_WIDTH = 190.0f;
static const int GAME_OVER_HEIGHT = 30.0f;
static const float GAME_OVER_POS_X = SCREEN_WIDTH * 0.5f;
static const float GAME_OVER_POS_Y = 615.0f;

static const int NEXT_SCENE_FRAME = 240;

static const float BULLET_SPEED = 15.0f;
static int tex = 0;

static GameOver* g_pGameOver;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Over_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/gameover.png", TEX_GAME_OVER_WIDTH, TEX_GAME_OVER_HEIGHT);
	Texture_Load();

	g_pGameOver = new GameOver;
	g_pGameOver->is_used = false;
	g_pGameOver->position.x = GAME_OVER_POS_X;
	g_pGameOver->position.y = GAME_OVER_POS_Y;
	
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Over_Uninit(void)
{
	delete g_pGameOver;
	g_pGameOver = 0;

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Over_Update(void)
{
	if (!g_pGameOver->is_used) { return; }
	g_pGameOver->to_scene_frame--;
	if (g_pGameOver->to_scene_frame <= 0) {

	}
	if (Keyboard_IsTrigger(DIK_RETURN)) {
		PlaySound(SOUND_LABEL_SE_DECISION);
		//Fades(SCENE_GAME);
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Over_Draw(void)
{
	if (!g_pGameOver->is_used) { return; }

	float tx = g_pGameOver->position.x - GAME_OVER_WIDTH * 0.5f;
	float ty = g_pGameOver->position.y - GAME_OVER_HEIGHT * 0.5f;
	Sprite_Draw(tex, tx, ty, GAME_OVER_WIDTH, GAME_OVER_HEIGHT);
}

void Game_Over_Create(void)
{
	if (g_pGameOver->is_used) { return; }
	g_pGameOver->is_used = true;
	g_pGameOver->to_scene_frame = NEXT_SCENE_FRAME;
}




