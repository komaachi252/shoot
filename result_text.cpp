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
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "scene.h"
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
typedef struct Result_Text_tag {
	bool is_used;
	int tex;
	D3DXVECTOR2 position;
	bool is_nextscene;
}Result_Text;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static const int TEX_RESULT_LOGO_WIDTH = 142;
static const int TEX_RESULT_LOGO_HEIGHT = 30;
static const float RESULT_LOGO_WIDTH = 284.0f;
static const float RESULT_LOGO_HEIGHT = 60.0f;

static const float RESULT_POS_X = SCREEN_WIDTH * 0.5f;
static const float RESULT_POS_Y = -RESULT_LOGO_HEIGHT * 0.5f;
static const float LOGO_END_POS = (SCREEN_HEIGHT * 0.2f);


static const int TEX_ENTER_WIDTH = 208;
static const int TEX_ENTER_HEIGHT = 48;
static const float ENTER_WIDTH = 208.0f;
static const float ENTER_HEIGHT = 48.0f;
static const float ENTER_POS_X = SCREEN_WIDTH * 0.5f;
static const float ENTER_POS_Y = SCREEN_HEIGHT * 0.8f;
static const float RESULT_SPEED = 5.0f;

static Result_Text* g_pResult_Text;
static Result_Text* g_pResult_Enter;
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Result_Text_Init(void)
{
	g_pResult_Text = new Result_Text;
	g_pResult_Text->is_used = true;
	g_pResult_Text->tex = Texture_SetLoodFile("Asset/Texture/resultlogo.png", TEX_RESULT_LOGO_WIDTH, TEX_RESULT_LOGO_HEIGHT);
	g_pResult_Text->position.x = RESULT_POS_X;
	g_pResult_Text->position.y = RESULT_POS_Y;
	g_pResult_Text->is_nextscene = false;
	g_pResult_Enter = new Result_Text;
	g_pResult_Enter->is_used = false;
	g_pResult_Enter->tex = Texture_SetLoodFile("Asset/Texture/pressenter.png", TEX_ENTER_WIDTH, TEX_ENTER_HEIGHT);
	g_pResult_Enter->position.x = ENTER_POS_X;
	g_pResult_Enter->position.y = ENTER_POS_Y;
	g_pResult_Enter->is_nextscene = false;
	Texture_Load();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Result_Text_Uninit(void)
{
	Texture_Destroy(&g_pResult_Text->tex, 1);
	Texture_Destroy(&g_pResult_Enter->tex, 1);
	delete g_pResult_Text;
	g_pResult_Text = 0;
	delete g_pResult_Enter;
	g_pResult_Enter = 0;

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Result_Text_Update(void)
{
	if (g_pResult_Text->position.y <= LOGO_END_POS) {
		g_pResult_Text->position.y += RESULT_SPEED;
	}
	if (g_pResult_Text->position.y >= LOGO_END_POS) {
		g_pResult_Enter->is_used = true;
	}
	if (Keyboard_IsTrigger(DIK_RETURN)) {
		PlaySound(SOUND_LABEL_SE_DECISION);
		g_pResult_Text->is_nextscene = true;
		Fade_Start(60, D3DCOLOR_RGBA(0, 0, 0, 0), true);
	}
	if (g_pResult_Text->is_nextscene && !Fade_IsFade()) {
		Scene_SetNextScene(SCENE_TITLE);
	}

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Result_Text_Draw(void)
{
	float tx = g_pResult_Text->position.x - RESULT_LOGO_WIDTH * 0.5f;
	float ty = g_pResult_Text->position.y - RESULT_LOGO_HEIGHT * 0.5f;
	Sprite_Draw(g_pResult_Text->tex, tx, ty, RESULT_LOGO_WIDTH, RESULT_LOGO_HEIGHT);

	if (!g_pResult_Enter->is_used) { return; }
	tx = g_pResult_Enter->position.x - ENTER_WIDTH * 0.5f;
	ty = g_pResult_Enter->position.y - ENTER_HEIGHT * 0.5f;
	Sprite_Draw(g_pResult_Enter->tex, tx, ty, ENTER_WIDTH, ENTER_HEIGHT);
}

bool is_used_Result_Text(void)
{
	return g_pResult_Enter->is_used;
}