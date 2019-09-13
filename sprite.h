#pragma once
#ifndef SPRITE_H_
#define SPRITE_H_
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	テクスチャ処理[texture.h]


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++(^-^)++++*/
#include <d3d9.h>


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	プロトタイプ宣言
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Sprite_Draw(int textureId, float dx, float dy);
void Sprite_Draw(int textureId, float dx, float dy, float w, float h);
void Sprite_DrawScroll(int textureId, float dx, float dy, float w, float h, float u, float v);
void Sprite_DrawAlpha(int textureId, float dx, float dy, float w, float h, int alpha);
void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h);
void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy,float scale);
void Sprite_DrawScale(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float cx, float cy, float scale);
void Sprite_DrawMirror(int textureId, float dx, float dy, float w, float h);

void Sprite_SetColor(D3DCOLOR color);

//void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, int w, int h);


#endif //SPRITE_H_