#ifndef KOMACHI3D_H_
#define KOMACHI3D_H_
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	Direct3D�w�b�_[komachi3d.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   7/23(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include <windows.h>
#include <d3d9.h>

//��������������������������������������������������������������������������������
//   �v���g�^�C�v�錾
//��������������������������������������������������������������������������������
bool komachi3D_Init(HWND hWnd);
void komachi3D_Uninit(void);
LPDIRECT3DDEVICE9 GetDevice(void);


#endif //KOMACHI3D_H_