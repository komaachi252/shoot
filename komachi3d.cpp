//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	Direct3D����[komachi3d.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   7/23(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include <d3d9.h>
#include <windows.h>
#include "common.h"

//��������������������������������������������������������������������������������
//   �O���[�o���ϐ�
//��������������������������������������������������������������������������������
static LPDIRECT3D9 g_pD3D = NULL;//Direct3D�C���^�[�t�F�[�X�̎擾
static LPDIRECT3DDEVICE9 g_pDevice = NULL;//Direct3D�f�o�C�X�̎擾

//��������������������������������������������������������������������������������
//   ������
//��������������������������������������������������������������������������������
bool komachi3D_Init(HWND hWnd) 
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);//�C���^�t�F�[�X���擾�@NULL���Ԃ��ꂽ��G���[�@���b�Z�[�W�{�b�N�X�ŕ\��
	if (g_pD3D == NULL) {
		MessageBox(NULL, "�C���^�t�F�[�X���擾�o���܂���ł���", "�m�F", MB_OK);
	}

	D3DPRESENT_PARAMETERS d3dpp = {};//Direct3D�f�o�C�X�̎擾�ׂ̈̍\���̕ϐ�

	d3dpp.BackBufferWidth = SCREEN_WIDTH;//�o�b�N�o�b�t�@�̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//�o�b�N�o�b�t�@�̍���
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//�f�v�X16bit D24S8�ɕς���
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//fream��  IMMEDIATE�@fps�ő��@�`���ɂ����\���X�V����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;//fream��  IMMEDIATE�@fps�ő��@�`���ɂ����\���X�V����
														 //d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);
	if (FAILED(hr)) {
		MessageBox(hWnd, "�f�o�C�X���擾�o���܂���ł����B", "�G���[", MB_OK);
		return false;
	}
	return true;
}

//��������������������������������������������������������������������������������
//   �I������
//��������������������������������������������������������������������������������
void komachi3D_Uninit(void) 
{
	if (g_pDevice != NULL) {
		g_pDevice->Release();
		g_pDevice = NULL;
	}
	if (g_pD3D != NULL) {
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//��������������������������������������������������������������������������������
//   �f�o�C�X�擾
//��������������������������������������������������������������������������������
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pDevice;
}