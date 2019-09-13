#pragma once

#ifndef FADES_H_
#define FADES_H_

#include "common.h"



enum FADE_STATE {
	FADE_STATE_NONE,
	FADE_STATE_IN,
	FADE_STATE_OUT
};

void Fades_Init(void);
void Fades_Uninit(void);
void Fades_Update(void);
void Fades_Draw(void);

void Fades(SCENE nextScene);
FADE_STATE GetFadesState(void);

#endif