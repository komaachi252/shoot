//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	”wŒiˆ—[bg.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "texture.h"
#include "sprite.h"


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
typedef struct BG_tag {
	int tex;
	float u;
	float v;
}BG;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static const int BG_WIDTH = 1280;
static const int BG_HEIGHT = 720;

static const float BG1_SPEED = 0.002f;
static const float BG2_SPEED = 0.004f;
static const float BG3_SPEED = 0.006f;

BG bg1, bg2,bg3;



//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void BG_Init(void)
{
	bg1.tex = Texture_SetLoodFile("Asset/Texture/space1.png", BG_WIDTH, BG_HEIGHT);
	bg2.tex = Texture_SetLoodFile("Asset/Texture/space2.png", BG_WIDTH, BG_HEIGHT);
	bg3.tex = Texture_SetLoodFile("Asset/Texture/space3.png", BG_WIDTH, BG_HEIGHT);
	bg1.u = 0.0f;
	bg2.u = 0.0f;
	bg3.u = 0.0f;
	bg1.v = 0.0f;
	bg2.v = 0.0f;
	bg3.v = 0.0f;
	Texture_Load();
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void BG_Uninit(void)
{
	Texture_Destroy(&bg1.tex,1);
	Texture_Destroy(&bg2.tex,1);
	Texture_Destroy(&bg3.tex,1);

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void BG_Update(void)
{
	bg1.u += BG1_SPEED;
	bg2.u += BG2_SPEED;
	bg3.u += BG3_SPEED;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void BG_Draw(void)
{
	Sprite_DrawScroll(bg1.tex, 0.0f, 0.0f, BG_WIDTH, BG_HEIGHT, bg1.u, bg1.v);
	Sprite_DrawScroll(bg2.tex, 0.0f, 0.0f, BG_WIDTH, BG_HEIGHT, bg2.u, bg2.v);
	Sprite_DrawScroll(bg3.tex, 0.0f, 0.0f, BG_WIDTH, BG_HEIGHT, bg3.u, bg3.v);
	//Sprite_Draw(bg1.tex, 0.0f, 0.0f, BG_WIDTH, BG_HEIGHT);
	//Sprite_Draw(bg2.tex, 0.0f, 0.0f, BG_WIDTH, BG_HEIGHT);

}

void BG_SetY(float y)
{
	bg1.v += y * BG1_SPEED;
	bg2.v += y * BG2_SPEED;
	bg3.v += y * BG3_SPEED;
}
