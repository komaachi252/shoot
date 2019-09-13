//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒV[ƒ“ˆ—[scene.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬ŽÒ –îˆêr
//                                                               ì¬“ú 9/10(‰Î)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
typedef void(*Func)(void);

static const Func INITS[] = {
	Title_Init,
	Game_Init,
	Result_Init,
};

static const Func UNINITS[] = {
	Title_Uninit,
	Game_Uninit,
	Result_Uninit
};

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static SCENE g_Scene = SCENE_TITLE;
static SCENE g_NextScene = SCENE_TITLE;
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Scene_Init(void)
{
	switch (g_NextScene)
	{
	case SCENE_TITLE:
		Title_Init();
		break;
	case SCENE_GAME:
		Game_Init();
		break;
	case SCENE_RESULT:
		Result_Init();
		break;
	default:
		break;
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Scene_Uninit(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Uninit();
		break;
	case SCENE_GAME:
		Game_Uninit();
		break;
	case SCENE_RESULT:
		Result_Uninit();
		break;
	default:
		break;
	}

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Scene_Update(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Update();
		break;
	case SCENE_GAME:
		Game_Update();
		break;
	case SCENE_RESULT:
		Result_Update();
		break;
	default:
		break;
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Scene_Draw(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Draw();
		break;
	case SCENE_GAME:
		Game_Draw();
		break;
	case SCENE_RESULT:
		Result_Draw();
		break;
	default:
		break;
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ŽŸ‚ÌƒV[ƒ“‚ð—\–ñ‚·‚éˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Scene_SetNextScene(SCENE next_scene)
{
	g_NextScene = next_scene;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//  ƒV[ƒ“Ø‚è‘Ö‚¦ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
bool Scene_Change(void)
{
	if (g_Scene != g_NextScene) {
		Scene_Uninit();
		if (g_NextScene == SCENE_END) {
			return true;
		}
		Scene_Init();
		g_Scene = g_NextScene;
	}
	return false;
}
