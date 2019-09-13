//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ˆ—[system.cpp]
//
//
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include <math.h>
#include <d3dx9.h>

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™

static float g_sin[360] = {};
static float g_cos[360] = {};
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void System_Init() 
{
	//  ƒTƒCƒ“ƒRƒTƒCƒ“ƒe[ƒuƒ‹ì¬
	for (int i = 0; i<360; i++) {
		g_sin[i] = (float)sin(i*D3DX_PI / 180);
		g_cos[i] = (float)cos(i*D3DX_PI / 180);
	}
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	Œ…Žæ“¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
unsigned GetDigit(unsigned num) 
{
	unsigned digit = 0;

	while(num != 0) {
		num / 10;
		digit++;
	}
	return digit;
}


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//   Šp“xŽæ“¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
int GetAngle(float from_x, float from_y, float to_x, float to_y) 
{
	return int(atan2(-double(from_y - to_y), double(from_x - to_x)) / D3DX_PI * 180 + 360) % 360;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	sinŽæ“¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
float Get_Sin(int angle)
{
	return g_sin[angle];
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	cosŽæ“¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
float Get_Cos(int angle)
{
	return g_cos[angle];
}



