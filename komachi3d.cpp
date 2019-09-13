//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	Direct3D処理[komachi3d.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   7/23(火)
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
#include <d3d9.h>
#include <windows.h>
#include "common.h"

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//   グローバル変数
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
static LPDIRECT3D9 g_pD3D = NULL;//Direct3Dインターフェースの取得
static LPDIRECT3DDEVICE9 g_pDevice = NULL;//Direct3Dデバイスの取得

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//   初期化
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
bool komachi3D_Init(HWND hWnd) 
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);//インタフェースを取得　NULLが返されたらエラー　メッセージボックスで表示
	if (g_pD3D == NULL) {
		MessageBox(NULL, "インタフェースを取得出来ませんでした", "確認", MB_OK);
	}

	D3DPRESENT_PARAMETERS d3dpp = {};//Direct3Dデバイスの取得の為の構造体変数

	d3dpp.BackBufferWidth = SCREEN_WIDTH;//バックバッファの幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//バックバッファの高さ
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//デプス16bit D24S8に変える
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//fream数  IMMEDIATE　fps最速　描画後にすぐ表示更新する
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;//fream数  IMMEDIATE　fps最速　描画後にすぐ表示更新する
														 //d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);
	if (FAILED(hr)) {
		MessageBox(hWnd, "デバイスが取得出来ませんでした。", "エラー", MB_OK);
		return false;
	}
	return true;
}

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//   終了処理
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
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

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//   デバイス取得
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pDevice;
}