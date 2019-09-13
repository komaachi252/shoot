//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒwƒbƒ_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#pragma once
#ifndef ACE_BOSS_H_
#define ACE_BOSS_H_

#include "collision.h"
#include "item.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
#define ACE_MAX_HP (30)
#define NORMAL_BULLET_DAMAGE (1)
#define METEOR_BULLET_DAMAGE (2)

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™



//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Ace_Init(void);	//‰Šú‰»ŠÖ”
void Ace_Uninit(void);	//I—¹ˆ—ŠÖ”
void Ace_Update(void);	//XVˆ—
void Ace_Draw(void);    //•`‰æˆ—
void Ace_Create(void);
bool is_used_Ace(void);
void Ace_Destroy(void);
Circle* Ace_get_collision(void);// ’†g‘‚«Š·‚¦‚È‚¢ƒAƒs[ƒ‹‚ÅƒRƒ“ƒXƒg‚Â‚¯‚é
void Ace_Turn(float y);
float Get_Ace_Pos_X(void);
float Get_Ace_Pos_Y(void);
void Ace_Sub_HP(Item_Type type);
void Ace_Break(void);
bool is_collision_Ace(void);

#endif
