//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒwƒbƒ_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#pragma once
#ifndef ENEMY_BULLET_H_
#define ENEMY_BULLET_H_

#include "collision.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
#define ENEMY_BULLET_MAX (64)

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™



//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Enemy_Bullet_Init(void);	//‰Šú‰»ŠÖ”
void Enemy_Bullet_Uninit(void);	//I—¹ˆ—ŠÖ”
void Enemy_Bullet_Update(void);	//XVˆ—
void Enemy_Bullet_Draw(void);    //•`‰æˆ—
void Enemy_Bullet_Create(float x, float y);
bool is_used_Enemy_Bullet(int index);
void Enemy_Bullet_Destroy(int index);
Circle* Enemy_Bullet_Get_Collision(int index); // ’†g‘‚«Š·‚¦‚È‚¢ƒAƒs[ƒ‹‚ÅƒRƒ“ƒXƒg‚Â‚¯‚é
void Enemy_Bullet_Turn_Over(int index);
bool is_Enemy_Turn_Over(int index);

#endif
