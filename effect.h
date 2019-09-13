//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	’eˆ—[bullet.h]
//
//
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#pragma once
#ifndef EFFECT_H_
#define EFFECT_H_


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
#define EFFECT_MAX (1024)

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Effect_Init(void);	// ‰Šú‰»ŠÖ”
void Effect_Uninit(void); // I—¹ˆ—ŠÖ”
void Effect_Update(void); // XVˆ—
void Effect_Draw(void);// •`‰æˆ—
void Effect_Create(float x, float y, D3DCOLOR color, int lifeFrame);
void Effect_Create(float x, float y, D3DCOLOR color, int lifeFrame, float scale); // ƒGƒtƒFƒNƒg‚ÌŠg‘å—¦‚à“ü‚ê‚é

#endif