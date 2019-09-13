#ifndef KOMACHI3D_H_
#define KOMACHI3D_H_
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	Direct3Dƒwƒbƒ_[komachi3d.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   7/23(‰Î)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include <windows.h>
#include <d3d9.h>

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//   ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
bool komachi3D_Init(HWND hWnd);
void komachi3D_Uninit(void);
LPDIRECT3DDEVICE9 GetDevice(void);


#endif //KOMACHI3D_H_