//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒAƒjƒ[ƒVƒ‡ƒ“ˆ—[pattern.cpp]
//
//
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "texture.h"
#include "sprite.h"

#define COCO_WALK_R_PATTERN_MAX (5)
#define COCO_WALK_R_PATTERN_MAX_U (2)


static int anitex = 0;

void PatternAnim_Init(void)
{
	anitex = Texture_SetLoodFile("Asset/Texture/runningman100.png", 700, 400);


}

void PatternAnim_Draw(float dx, float dy, int frameCount)
{
	//int pattern = frameCount % COCO_WALK_R_PATTERN_MAX;
	int pattern1 = frameCount / 6  % COCO_WALK_R_PATTERN_MAX;
	int pattern2 = (frameCount / 6 / COCO_WALK_R_PATTERN_MAX) % COCO_WALK_R_PATTERN_MAX_U;


	//‚±‚±‰E‚¾‚¿•`‰æ
	Sprite_Draw(anitex,dx,dy,pattern1* 140, pattern2 * 200,140,200);
	//pattern % 5 * 32

}

void PatternAnim_Draw(int tex_id, float dx, float dy, float w, float h, int framelen, int framecnt)
{

	Sprite_Draw(tex_id, dx, dy, framecnt % framelen * w, framecnt / framelen * h, w, h);

}