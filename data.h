//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒwƒbƒ_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#pragma once
#ifndef DATA_H_
#define DATA_H_

#include <d3dx9.h>

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
#define  DATA_MAX (4)   // ˆµ‚¤ƒf[ƒ^” —v‘f‚R”Ô–Ú‚ÉŒ»Ý‚ÌƒvƒŒƒCƒ„[‚ð“ü‚ê‚é

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
enum Stage_Number {
	STAGE_1,
	STAGE_2,
	STAGE_3
};


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Data_Init(void);	//‰Šú‰»ŠÖ”
void Data_Uninit(void);	//I—¹ˆ—ŠÖ”
void Set_Stage_Number(Stage_Number num);
Stage_Number Get_Stage_Number(void);
void Set_Player_Pos(D3DXVECTOR2 pos);
D3DXVECTOR2 Get_Player_Pos(void);
void Set_Score(int score);
int Get_Score(int i);
int Get_CurrentPlayer(void);  // Œ»Ý‚ÌƒvƒŒƒCƒ„[‚Ì—v‘f”Ô†‚ª–ß‚è’l‚Å‚·
#endif
