//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒGƒlƒ~[¶¬ˆ—[Enemygenerate.cpp]
//
//
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "enemy.h"
#include "common.h"
#include "urchins_enemy.h"
#include "rays_enemy.h"
#include "anemones_enemy.h"
#include "ground.h"


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
typedef struct EnemyGenerate_tag {
	int frame;
	float y;
	ENEMY_TYPE type;
}EnemyGenerate;

static const EnemyGenerate ENEMY_GENERATE[] = {
	{60,128.0f,URCHINS},
	{240,128.0f,URCHINS},
	{120,128.0f,URCHINS},
	{120,128.0f,URCHINS},

};

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static const int CREATE_GROUND_FRAME[] = { 540,1200};
static const int ENENMY_GENERATE_MAX = sizeof(ENEMY_GENERATE) / sizeof(ENEMY_GENERATE[0]);   // ƒGƒlƒ~[Å‘å¶¬”
static const int GROUND_MAX = sizeof(CREATE_GROUND_FRAME) / sizeof(CREATE_GROUND_FRAME[0]);   // ’n–ÊÅ‘å¶¬”


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static int EnemyGenerate_Arrow = 0;  // Ëo‚µ‚½”
static int EnemyGenerate_FrameCount = 0;   // ƒtƒŒ[ƒ€ƒJƒEƒ“ƒ^[


static int Ground_itr = 0;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void EnemyGenerate_Init(void) 
{
	EnemyGenerate_Arrow = 0;
	EnemyGenerate_FrameCount = 0;
	Ground_itr = 0;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void EnemyGenerate_Uninit(void)
{
	EnemyGenerate_Arrow = 0;
	EnemyGenerate_FrameCount = 0;

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void EnemyGenerate_Update(void)
{
	for (; EnemyGenerate_Arrow < ENENMY_GENERATE_MAX; EnemyGenerate_Arrow++) {
		if (ENEMY_GENERATE[EnemyGenerate_Arrow].frame == EnemyGenerate_FrameCount) {
			Enemy_Create(ENEMY_GENERATE[EnemyGenerate_Arrow].type, ENEMY_GENERATE[EnemyGenerate_Arrow].y);
			continue;
		}else if (ENEMY_GENERATE[EnemyGenerate_Arrow].frame > EnemyGenerate_FrameCount) {
			break;
		}

	}
	for (; Ground_itr < GROUND_MAX; Ground_itr++) {
		if (CREATE_GROUND_FRAME[Ground_itr] >= EnemyGenerate_FrameCount) {
			Ground_Create();
			continue;
		}else if (CREATE_GROUND_FRAME[Ground_itr] >= EnemyGenerate_FrameCount) {
			break;
		}
	}

	EnemyGenerate_FrameCount++;
}