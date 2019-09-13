#include "common.h"
#include "texture.h"
#include "sprite.h"
#include "fades.h"


static FADE_STATE g_fadeState = FADE_STATE_NONE;
static SCENE g_fadeNextScene = SCENE_NONE;

static int g_fadeAlpha = 0;

static int TEX_SIZE = 16;

static int FADE_SPEED = 2;

static int tex;

void Fades_Init(void)
{
	g_fadeState = FADE_STATE_NONE;
	g_fadeNextScene = SCENE_NONE;
	g_fadeAlpha = 0;
	tex = Texture_SetLoodFile("Asset/Texture/fade.png", TEX_SIZE, TEX_SIZE);
	Texture_Load();
}


void Fades_Uninit(void)
{
	Texture_Destroy(&tex,1);
}


void Fades_Update(void)
{
	if (g_fadeState == FADE_STATE_OUT) {
		g_fadeAlpha += FADE_SPEED;
		if (g_fadeAlpha >= 255) {
			g_fadeAlpha = 255;
			g_fadeState = FADE_STATE_IN;
			SetScene(g_fadeNextScene);
		}
	}else if (g_fadeState == FADE_STATE_IN) {
		if (g_fadeAlpha <= 0) {
			g_fadeAlpha = 0;
			g_fadeState = FADE_STATE_NONE;
		}
		g_fadeAlpha -= FADE_SPEED * 0.2f;//20ƒtƒŒ[ƒ€
	}
}


void Fades_Draw(void)
{
	if (g_fadeState == FADE_STATE_NONE) {
		return;
	}

	//Sprite_DrawAlpha(tex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,g_fadeAlpha);
	Sprite_DrawAlpha(tex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,g_fadeAlpha);
}
void Fades(SCENE nextScene)
{
	g_fadeNextScene = nextScene;

	g_fadeState = FADE_STATE_OUT;
}
FADE_STATE GetFadesState(void)
{
	return g_fadeState;
}