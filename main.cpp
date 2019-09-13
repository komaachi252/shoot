//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	���C������[main.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   7/23(��)													��@��r
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c

#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "common.h"
#include "komachi3d.h"
#include "texture.h"
#include "sprite.h"
#include "system_timer.h"
#include "debug_font.h"
#include "input.h"
#include "Game.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "data.h"
#include "system.h"
#include "sound.h"
#include "number.h"
#include "effect.h"
#include "engine.h"
#include "scene.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define CLASS_NAME     "GameWindow"
//#define WINDOW_CAPTION "�I���W�i���Q�[��(����)"
#define WINDOW_CAPTION "�V�[���J��"
#define FPS_MEASUREMENT_TIME (1.0f)
#define WINDOW_STYLE  (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX)) //�E�B���h�E�̃X�^�C�����`

//��������������������������������������������������������������������������������
//   �v���g�^�C�v�錾
//��������������������������������������������������������������������������������
LRESULT CALLBACK WndProc(HWND hWind, UINT uMsg, WPARAM wParam, LPARAM lParam);
static bool Init(HWND hWnd, HINSTANCE hInstance);//�������֐��C�j�V�����C�Y
static void Uninit(void);//�I�������֐��t�@�C�i���C�Y
static void Update(void);//
static void Draw(void);//

//��������������������������������������������������������������������������������
//   �\���̐錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//   �O���[�o���ϐ�
//��������������������������������������������������������������������������������
static LPDIRECT3DDEVICE9  g_pDevice = NULL;


static int g_FrameCount = 0; // �t���[���J�E���^�[
static int g_FPSBaseFrameCount = 0; // FPS�v���̊�ƂȂ�t���[���J�E���^�[
static double g_FPSBaseTime = 0.0; // FPS�v���̊�ƂȂ鎞��
static double g_StaticFrameTime = 0; // �t���[���Œ�p�v������
static float g_FPS = 0.0f; // FPS

//��������������������������������������������������������������������������������
//   ���C��
//��������������������������������������������������������������������������������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASS wc = {};//0�ŏ�����
	wc.lpfnWndProc = WndProc;//�֐���
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wc);

	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	AdjustWindowRect(&window_rect,WINDOW_STYLE, FALSE);

	int window_width   = window_rect.right  - window_rect.left;
	int window_height  = window_rect.bottom - window_rect.top;
	int desktop_width  = GetSystemMetrics(SM_CXSCREEN);//���j�^�[��
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);//���j�^�[����
	int window_x       = max((desktop_width - window_width) / 2,0);//��ʐ^�񒆂̍��W�𒲂ׂ�X
	int window_y       = max((desktop_height - window_height) / 2,0);//Y
	HWND hWnd = CreateWindow(
		CLASS_NAME,//�N���X��
		WINDOW_CAPTION,//�E�B���h�E�̖��O
		WINDOW_STYLE,//�E�B���h�E�̌` �E�B���h�E�T�C�Y�Œ�
		window_x,//���W����X�@�e�L�X�g���܂߂ĕ�����
		window_y,//Y
		window_width,//��
		window_height,//����
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MSG msg = {};

	if (!Init(hWnd,hInstance)) {
		return -1;
	}
	while ( WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}else {//�Q�[���̏���
			double time = SystemTimer_GetTime();
			if (time - g_StaticFrameTime < 1.0f / 60.0f) {
				Sleep(0);
			}else {
				g_StaticFrameTime = time;
				Update();
				Draw();
				if (Scene_Change()) {
					break;
				}
			}
		}
	}
	Uninit();

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KEYDOWN://�L�[�̓��͂�������
		if (wParam == VK_ESCAPE) {//�L�[�̖��O�������Ă��� Escape�L�[�ŏI������悤�ɂ���
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE://�E�B���h�E����Ƃ��ɏo��
		if (MessageBox(hWnd, "�{���ɏI�����Ă���낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);//WM_QUIT��GetMessage�ɏo��
		return 0;
	};
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//���̃��b�Z�[�W������������
}

//��������������������������������������������������������������������������������
//   ������
//��������������������������������������������������������������������������������
bool Init(HWND hWnd, HINSTANCE hInstance)
{
	
	komachi3D_Init(hWnd);

	g_pDevice = GetDevice();

	Data_Init();

	Fade_Init();

	System_Init();

	// systemtimer������
	SystemTimer_Initialize();

	// �V�X�e���^�C�}�[�̋N��
	SystemTimer_Start();

	// FPS�v���p�ϐ��Q�̏�����
	g_FrameCount = g_FPSBaseFrameCount = 0;
	g_FPS = 0.0f;

	g_FPSBaseTime = SystemTimer_GetTime();
	g_StaticFrameTime =	g_FPSBaseTime ;

	DebugFont_Initialize();

	Keyboard_Initialize(hInstance, hWnd);

	InitSound(hWnd);
	
	Number_Init();

	Effect_Init();

	Engine_Init();


	Scene_Init();

	Sprite_SetColor(0xFFFFFFFF);
	//Fade(SCENE_TITLE);
	return true;

}

//��������������������������������������������������������������������������������
//   �I������
//��������������������������������������������������������������������������������
void Uninit(void)
{
	Texture_Destroy();

	Fade_Uninit();

	Data_Uninit();

	komachi3D_Uninit();

	DebugFont_Finalize();

	Keyboard_Finalize();

	UninitSound();

	Number_Uninit();

	Effect_Uninit();

	Engine_Uninit();

	//Scene_Uninit();
}

//��������������������������������������������������������������������������������
//   �X�V����
//��������������������������������������������������������������������������������
void Update(void) // �X�V����
{

	Keyboard_Update();

	Scene_Update();

	Fade_Update();

	Effect_Update();

	// �t���[���J�E���g�̍X�V
	g_FrameCount++;

	// ���݂̃V�X�e�����Ԃ̎擾
	double time = SystemTimer_GetTime();

	// �O���FPS�v�����Ԃ��K�莞�Ԍo���Ă�����FPS�v��
	if (time - g_FPSBaseTime >= FPS_MEASUREMENT_TIME) { //�@���̎��ԁ@�|�@�Ƃ��Ă���������

		// FPS�v�Z(�O�񂩂�̌o�߃t���[�����o�ߎ���)
		g_FPS = (float)((g_FrameCount - g_FPSBaseFrameCount) / (time - g_FPSBaseTime));

		// FPS�v���̊�ɂȂ�ϐ����X�V
		g_FPSBaseFrameCount = g_FrameCount;
		g_FPSBaseTime = time;
	}
}

//��������������������������������������������������������������������������������
//   �`�揈��
//��������������������������������������������������������������������������������
void Draw(void)
{
	//��ʂ̃N���A
	//g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA( 80,100, 200, 255), 1.0f, 0);
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA( 0, 0, 0, 255), 1.0f, 0);
	g_pDevice->BeginScene();
	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // �G�t�F�N�g�̎��K�{

	Scene_Draw();

	Effect_Draw();

	Fade_Draw();

	DebugFont_Draw(0, 0, "%f",g_FPS);

	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);


}
