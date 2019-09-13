//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[Game.cpp]
//
//
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "EnemyGenerater.h"
#include "Judgement.h"
#include "number.h"
#include "explosion.h"
#include "scoredraw.h"
#include "score.h"
#include "common.h"
#include "sound.h"
#include "Induction_bullet.h"
#include "bg.h"
#include "urchins_enemy.h"
#include "enemy_bullet.h"
#include "rays_enemy.h"
#include "anemones_enemy.h"
#include "ground.h"	
#include "ace_boss.h"
#include "item.h"
#include "trident_bullet.h"
#include "penetrate_bullet.h"
#include "meteor_bullet.h"
#include "shield.h"
#include "playertype_draw.h"
#include "gameover.h"
#include "GameMaster.h"
#include "boss_hp.h"
#include "fade.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Init(void)
{
	Player_Init();
	Bullet_Init();
	Trident_Bullet_Init();
	Penetrate_Init();
	Meteor_Bullet_Init();
	Shield_Init();
	Enemy_Init();
	Urchins_Init();
	Rays_Init();
	Anemone_Init();
	Ace_Init();
	Enemy_Bullet_Init();
	EnemyGenerate_Init();
	Explosion_Init();
	Score_Init();
	Induction_Bullet_Init();
	Item_Init();
	BG_Init();
	Ground_Init();
	Player_Type_Init();
	Judgement_Init();
	Game_Over_Init();
	Game_Master_Init();
	Boss_HP_Init();
	PlaySound(SOUND_LABEL_BGM_GAME);
	Fade_Start(60,D3DCOLOR_RGBA(0,0,0,0),false);
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Uninit(void)
{
	StopSound();
	Player_Type_Uninit();
	Ground_Uninit();
	BG_Uninit();
	Player_Uninit();
	Trident_Bullet_Uninit();
	Penetrate_Uninit();
	Meteor_Bullet_Uninit();
	Shield_Uninit();
	Bullet_Uninit();
	Enemy_Uninit();
	Urchins_Uninit();
	Rays_Uninit();
	Ace_Uninit();
	Anemone_Uninit();
	Enemy_Bullet_Uninit();
	EnemyGenerate_Uninit();
	Explosion_Uninit();
	Score_Uninit();
	Item_Uninit();
	Induction_Bullet_Uninit();
	Judgement_Uninit();
	Game_Over_Uninit();
	Game_Master_Uninit();
	Boss_HP_Uninit();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Update(void)
{
	//Game_Master_Update();
	Player_Update();
	Bullet_Update();
	Trident_Bullet_Update();
	Penetrate_Update();
	Meteor_Bullet_Update();
	Shield_Update();
	Enemy_Update();
	Urchins_Update();
	Rays_Update();
	Anemone_Update();
	Ace_Update();
	Enemy_Bullet_Update();
	EnemyGenerate_Update();
	Judgement_Update();
	Explosion_Update();
	Induction_Bullet_Update();
	Item_Update();
	BG_Update();
	Ground_Update();
	Game_Over_Update();
	Boss_HP_Update();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Game_Draw(void)
{
	BG_Draw();
	Ground_Draw();
	Item_Draw();
	Enemy_Draw();
	Urchins_Draw();
	Rays_Draw();
	Anemone_Draw();
	Ace_Draw();
	Enemy_Bullet_Draw();
	Bullet_Draw();
	Trident_Bullet_Draw();
	Penetrate_Draw();
	Meteor_Bullet_Draw();
	Player_Draw();
	Shield_Draw();
	Induction_Bullet_Draw();
	Explosion_Draw();
	Player_Type_Draw();
	Score_Draw(get_score(),1200.0f,600.0f,7);
	Game_Over_Draw();
	Boss_HP_Draw();
}