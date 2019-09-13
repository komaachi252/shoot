/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	スプライト処理[sprite.cpp]


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++(^-^)++++*/
#define _CRT_SECURE_NO_WARNINGS
#include <d3d9.h>
#include <d3dx9.h>
#include "komachi3d.h"
#include  "common.h"
#include "texture.h"


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	マクロ定義
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define FILENAME_MAX    (128)
#define TEXTUREDATA_MAX  (64)



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	構造体宣言
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
typedef struct vertex2d_tag {//Draw関数用頂点構造体

	D3DXVECTOR4 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
}Vertex2d;
#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	グローバル変数
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
static float x = 0;

static D3DCOLOR g_color;
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	スプライト表示関数
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Sprite_Draw(int textureId, float dx, float dy)
{

	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	//頂点データを用意
	Vertex2d v[4] = {
		{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR4(dx + w - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR4(dx - 0.5f,dy  + h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR4(dx + w - 0.5f,dy + h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f) }

	};
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//FVF
	pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャ
	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(textureId);

	pDevice->SetTexture(0, pTexture);

	//DrawPrimitiveUP
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	スプライト表示関数(幅高さ指定)
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Sprite_Draw(int textureId, float dx, float dy, float w, float h)
{
	
	//頂点データを用意
	Vertex2d v[4] = {
		{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f, 0.0f, 1.0f),g_color,D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR4(dx + w - 0.5f,dy - 0.5f, 0.0f, 1.0f),g_color,D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR4(dx - 0.5f,dy + h - 0.5f, 0.0f, 1.0f),g_color,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR4(dx + w - 0.5f,dy + h - 0.5f, 0.0f, 1.0f),g_color,D3DXVECTOR2(1.0f,1.0f) }

	};
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//FVF
	pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャ
	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(textureId);

	pDevice->SetTexture(0, pTexture);

	//DrawPrimitiveUP
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

}

void Sprite_DrawMirror(int textureId, float dx, float dy, float w, float h)
{
	
	//頂点データを用意
	Vertex2d v[4] = {
		{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR4(dx + w - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR4(dx - 0.5f,dy + h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f) },
		{ D3DXVECTOR4(dx + w - 0.5f,dy + h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f) }

	};
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//FVF
	pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャ
	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(textureId);

	pDevice->SetTexture(0, pTexture);

	//DrawPrimitiveUP
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

}



void Sprite_DrawScroll(int textureId, float dx, float dy, float w, float h, float u, float v)
{
	//頂点データを用意
	Vertex2d vd[4] = {
		{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u,v) },
	{ D3DXVECTOR4(dx + w - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f + u,v) },
	{ D3DXVECTOR4(dx - 0.5f,dy + h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u,1.0f + v) },
	{ D3DXVECTOR4(dx + w - 0.5f,dy + h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f + u,1.0f + v) }

	};
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//FVF
	pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャ
	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(textureId);

	pDevice->SetTexture(0, pTexture);

	//DrawPrimitiveUP
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vd, sizeof(Vertex2d));

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	スプライト表示関数(幅高さ指定)
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Sprite_DrawAlpha(int textureId, float dx, float dy, float w, float h, int alpha)
{
	
	//頂点データを用意
	Vertex2d v[4] = {
		{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,alpha),D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR4(dx + w - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,alpha),D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR4(dx - 0.5f,dy + h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,alpha),D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR4(dx + w - 0.5f,dy + h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,alpha),D3DXVECTOR2(1.0f,1.0f) }

	};
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//FVF
	pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャ
	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(textureId);

	pDevice->SetTexture(0, pTexture);

	//DrawPrimitiveUP
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

}



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	スプライト切り取り表示関数
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h)
{

	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;

	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;

	//頂点データを用意
	Vertex2d v[4] = {
		{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(dx + cut_w - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(dx - 0.5f,dy + cut_h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(dx + cut_w - 0.5f,dy + cut_h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v1) }

	};
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//FVF
	pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャ
	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(textureId);

	pDevice->SetTexture(0, pTexture);

	//DrawPrimitiveUP
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
スプライト切り取り表示関数 回転
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy,float scale)
{

	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;//答え　回転　平行移動　戻す 

	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);//平行移動
	D3DXMatrixTranslation(&mtxIT,  cx,  cy, 0.0f);//平行移動戻す
	D3DXMatrixRotationZ(&mtxR, angle);//回転
	D3DXMatrixScaling(&mtxS, scale, scale, 1.0f);//拡大

	//順番に意味がある
	mtxW = mtxT * mtxS * mtxR * mtxIT;//平行移動して回転して平行移動戻す

	//D3DXMATRIX mtxRot;
	//D3DXMatrixRotationZ(&mtxRot,angle);

	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;

	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;

	x -= 2.0f;
	//頂点データを用意
	Vertex2d v[4] = {
		{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(dx + cut_w - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(dx - 0.5f,dy + cut_h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(dx + cut_w - 0.5f,dy + cut_h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v1) }

	};
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//FVF
	pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャ
	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(textureId);

	pDevice->SetTexture(0, pTexture);

	//DrawPrimitiveUP
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}

void Sprite_DrawScale(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float cx, float cy, float scale)
{

	D3DXMATRIX mtxW, mtxT, mtxIT, mtxS;//答え　回転　平行移動　戻す 

	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);//平行移動
	D3DXMatrixTranslation(&mtxIT, cx, cy, 0.0f);//平行移動戻す
	D3DXMatrixScaling(&mtxS, scale, scale, 1.0f);//拡大
												 //順番に意味がある
	mtxW = mtxT * mtxS * mtxIT;//平行移動して回転して平行移動戻す

									  //D3DXMATRIX mtxRot;
									  //D3DXMatrixRotationZ(&mtxRot,angle);

	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;

	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;

	x -= 2.0f;
	//頂点データを用意
	Vertex2d v[4] = {
	{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v0) },
	{ D3DXVECTOR4(dx + cut_w - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v0) },
	{ D3DXVECTOR4(dx - 0.5f,dy + cut_h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v1) },
	{ D3DXVECTOR4(dx + cut_w - 0.5f,dy + cut_h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v1) }

	};
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//FVF
	pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャ
	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(textureId);

	pDevice->SetTexture(0, pTexture);

	//DrawPrimitiveUP
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
スプライト切り取り表示関数 回転 ポリゴン中心座標
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy)
{

	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;//答え　回転　平行移動　戻す 拡大

	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);//平行移動
	D3DXMatrixTranslation(&mtxIT, cx, cy, 0.0f);//平行移動戻す
	D3DXMatrixRotationZ(&mtxR, angle);//回転
	D3DXMatrixScaling(&mtxS, 1.0f, 1.0f, 1.0f);//拡大

											   //順番に意味がある
	mtxW = mtxT * mtxR * mtxS * mtxIT;//平行移動して回転して平行移動戻す

							   //D3DXMATRIX mtxRot;
							   //D3DXMatrixRotationZ(&mtxRot,angle);

	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;

	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;

	x -= 2.0f;
	//頂点データを用意
	Vertex2d v[4] = {
		{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v0) },
	{ D3DXVECTOR4(dx + cut_w - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v0) },
	{ D3DXVECTOR4(dx - 0.5f,dy + cut_h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v1) },
	{ D3DXVECTOR4(dx + cut_w - 0.5f,dy + cut_h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v1) }

	};
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//FVF
	pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャ
	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(textureId);

	pDevice->SetTexture(0, pTexture);

	//DrawPrimitiveUP
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	スプライト切り取り表示関数
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, int w, int h)
{

	int tw = Texture_GetWidth(textureId);
	int th = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)tw;
	float v0 = cut_y / (float)th;

	float u1 = (cut_x + cut_w) / (float)tw;
	float v1 = (cut_y + cut_h) / (float)th;


	//頂点データを用意
	Vertex2d v[4] = {
		{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v0) },
	{ D3DXVECTOR4(dx + w - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v0) },
	{ D3DXVECTOR4(dx - 0.5f,dy + h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v1) },
	{ D3DXVECTOR4(dx + w - 0.5f,dy + h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v1) }

	};
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//FVF
	pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャ
	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(textureId);

	pDevice->SetTexture(0, pTexture);

	//DrawPrimitiveUP
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

}

void Sprite_SetColor(D3DCOLOR color)
{
	g_color = color;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	スプライト切り取り表示関数(幅高さ指定版)
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h,int w, int h)
{

	int tw = Texture_GetWidth(textureId);
	int th = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)tw;
	float v0 = cut_y / (float)th;

	float u1 = (cut_x + cut_w) / (float)tw;
	float v1 = (cut_y + cut_h) / (float)th;


	//頂点データを用意
	Vertex2d v[4] = {
		{ D3DXVECTOR4(dx - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(dx + w - 0.5f,dy - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(dx - 0.5f,dy + h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(dx + w - 0.5f,dy + h - 0.5f, 0.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v1) }

	};
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//FVF
	pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャ
	LPDIRECT3DTEXTURE9 pTexture = Texture_GetTexture(textureId);

	pDevice->SetTexture(0, pTexture);

	//DrawPrimitiveUP
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

}*/

