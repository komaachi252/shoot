//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <Windows.h>

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM_TITLE,
	SOUND_LABEL_BGM_GAME,
	SOUND_LABEL_BGM_BOSS,
	SOUND_LABEL_SE_RESULT,
	SOUND_LABEL_SE_NORMAL_SHOT,		// 弾発射音
	SOUND_LABEL_SE_PENETRATE_SHOT,
	SOUND_LABEL_SE_SIDE_SHOT,
	SOUND_LABEL_SE_METEOR_SHOT,
	SOUND_LABEL_SE_ENEMY_SHOT,
	SOUND_LABEL_SE_INDUCTION_SHOT,
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_SE_ITEM,
	SOUND_LABEL_SE_REFLECT,
	SOUND_LABEL_SE_DAMAGE,
	SOUND_LABEL_SE_DECISION,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
