//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	メイン処理[main.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   7/23(火)													矢吹　一俊
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡

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

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	定数定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
#define CLASS_NAME     "GameWindow"
//#define WINDOW_CAPTION "オリジナルゲーム(α版)"
#define WINDOW_CAPTION "シーン遷移"
#define FPS_MEASUREMENT_TIME (1.0f)
#define WINDOW_STYLE  (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX)) //ウィンドウのスタイルを定義

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//   プロトタイプ宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
LRESULT CALLBACK WndProc(HWND hWind, UINT uMsg, WPARAM wParam, LPARAM lParam);
static bool Init(HWND hWnd, HINSTANCE hInstance);//初期化関数イニシャライズ
static void Uninit(void);//終了処理関数ファイナライズ
static void Update(void);//
static void Draw(void);//

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//   構造体宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆


//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//   グローバル変数
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
static LPDIRECT3DDEVICE9  g_pDevice = NULL;


static int g_FrameCount = 0; // フレームカウンター
static int g_FPSBaseFrameCount = 0; // FPS計測の基となるフレームカウンター
static double g_FPSBaseTime = 0.0; // FPS計測の基となる時間
static double g_StaticFrameTime = 0; // フレーム固定用計測時間
static float g_FPS = 0.0f; // FPS

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//   メイン
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASS wc = {};//0で初期化
	wc.lpfnWndProc = WndProc;//関数名
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wc);

	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	AdjustWindowRect(&window_rect,WINDOW_STYLE, FALSE);

	int window_width   = window_rect.right  - window_rect.left;
	int window_height  = window_rect.bottom - window_rect.top;
	int desktop_width  = GetSystemMetrics(SM_CXSCREEN);//モニター幅
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);//モニター高さ
	int window_x       = max((desktop_width - window_width) / 2,0);//画面真ん中の座標を調べるX
	int window_y       = max((desktop_height - window_height) / 2,0);//Y
	HWND hWnd = CreateWindow(
		CLASS_NAME,//クラス名
		WINDOW_CAPTION,//ウィンドウの名前
		WINDOW_STYLE,//ウィンドウの形 ウィンドウサイズ固定
		window_x,//座標左上X　テキストも含めて幅高さ
		window_y,//Y
		window_width,//幅
		window_height,//高さ
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
		}else {//ゲームの処理
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
	case WM_KEYDOWN://キーの入力があった
		if (wParam == VK_ESCAPE) {//キーの名前を持っている Escapeキーで終了するようにする
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE://ウィンドウ閉じるときに出る
		if (MessageBox(hWnd, "本当に終了してもよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);//WM_QUITをGetMessageに出す
		return 0;
	};
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//他のメッセージを処理したい
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//   初期化
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
bool Init(HWND hWnd, HINSTANCE hInstance)
{
	
	komachi3D_Init(hWnd);

	g_pDevice = GetDevice();

	Data_Init();

	Fade_Init();

	System_Init();

	// systemtimer初期化
	SystemTimer_Initialize();

	// システムタイマーの起動
	SystemTimer_Start();

	// FPS計測用変数群の初期化
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

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//   終了処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
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

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//   更新処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Update(void) // 更新時間
{

	Keyboard_Update();

	Scene_Update();

	Fade_Update();

	Effect_Update();

	// フレームカウントの更新
	g_FrameCount++;

	// 現在のシステム時間の取得
	double time = SystemTimer_GetTime();

	// 前回のFPS計測時間が規定時間経っていたらFPS計測
	if (time - g_FPSBaseTime >= FPS_MEASUREMENT_TIME) { //　今の時間　－　とっておいた時間

		// FPS計算(前回からの経過フレーム÷経過時間)
		g_FPS = (float)((g_FrameCount - g_FPSBaseFrameCount) / (time - g_FPSBaseTime));

		// FPS計測の基になる変数を更新
		g_FPSBaseFrameCount = g_FrameCount;
		g_FPSBaseTime = time;
	}
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//   描画処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Draw(void)
{
	//画面のクリア
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
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // エフェクトの時必須

	Scene_Draw();

	Effect_Draw();

	Fade_Draw();

	DebugFont_Draw(0, 0, "%f",g_FPS);

	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);


}
