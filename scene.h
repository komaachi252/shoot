//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒV[ƒ“ƒwƒbƒ_[scene.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               ì¬ŽÒ –îˆêr
//                                                               ì¬“ú 9/10(‰Î)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#pragma once
#ifndef SCENE_H_
#define SCENE_H_



//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	—ñ‹“Œ^éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
enum SCENE {
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_END,  //  ‚±‚ê‚ª“ü—Í‚³‚ê‚½‚çƒAƒvƒŠƒP[ƒVƒ‡ƒ“‚ÌI—¹
	SCENE_MAX
};

enum { SCENE_ENDO = 120 };

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Scene_Init(void);   //‰Šú‰»ŠÖ”
void Scene_Uninit(void);   //I—¹ˆ—ŠÖ”
void Scene_Update(void);   //XVˆ—
void Scene_Draw(void);   //•`‰æˆ—
void Scene_SetNextScene(SCENE next_scene);
bool Scene_Change(void);  // –ß‚è’l‚ªtrue‚ÌŽžƒAƒvƒŠƒP[ƒVƒ‡ƒ“‚ÌI—¹

#endif
