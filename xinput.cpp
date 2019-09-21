//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	Xinput����[xinput.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "xinput.h"
#include <windows.h>
//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
enum INPUT_STATE {
	NONE,
	PUSH,
	ENTER,
	EXIT
};
enum BUTTON {
	BUTTON_A,
	BUTTON_B,
	BUTTON_X,
	BUTTON_Y,
	BUTTON_MAX
};
enum { KEY_MAX = 32769 };
//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static WORD g_key[KEY_MAX] = {0};
static WORD g_old[KEY_MAX] = {0};
static XINPUT_STATE g_state;
static  DWORD XINPUT_MAX_CONTROLLERS = 4;
static INPUT_STATE g_input[BUTTON_MAX];
static int a;
//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������

bool Xinput_Init(HWND hWnd)
{
	a = 0;
	for (int i = 0; i < BUTTON_MAX; i++) {
		g_input[i] = NONE;
	}
	
	ZeroMemory(&g_state, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &g_state);

	for (int i = 0; i < KEY_MAX; i++) {
		g_old[i] = 0;
		g_key[i] = 0;
	}

	g_key[XINPUT_GAMEPAD_A] = g_state.Gamepad.wButtons;
	g_key[XINPUT_GAMEPAD_B] = g_state.Gamepad.wButtons;
	g_key[XINPUT_GAMEPAD_X] = g_state.Gamepad.wButtons;
	g_key[XINPUT_GAMEPAD_Y] = g_state.Gamepad.wButtons;
	g_key[XINPUT_GAMEPAD_START] = g_state.Gamepad.wButtons;


	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
		return true;
	}
	else
	{
		// Controller is not connected
		MessageBox(hWnd, "Xinput�I�u�W�F�N�g���Ȃ��ł�", "�x���I", MB_ICONWARNING);
		return false;
	}
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Xinput_Uninit(void)
{


}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Xinput_Update(void)
{
	XInputGetState(0, &g_state);

	if ((g_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(g_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		g_state.Gamepad.sThumbLX = 0;
		g_state.Gamepad.sThumbLY = 0;
	}
}

//��������������������������������������������������������������������������������
//	���͏���
//��������������������������������������������������������������������������������
bool Xinput_IsPress(int key)
{
	if (g_state.Gamepad.wButtons & key) {
		
		return true;
	}
	return false;
}

//��������������������������������������������������������������������������������
//	���͏���
//��������������������������������������������������������������������������������
bool Xinput_IsTrigger(int key)
{

	bool flag = false;
	g_key[key] = g_state.Gamepad.wButtons;

	if (g_key[key] & key && !(g_old[key])) {
		flag = true;
	}
	g_old[key] = g_key[key];
	return flag;
}

//��������������������������������������������������������������������������������
//	���͏���
//��������������������������������������������������������������������������������
bool Xinput_IsExit(int key)
{
	if (g_state.Gamepad.wButtons & key) {
		g_key[key] = g_state.Gamepad.wButtons;
		return false;
	}
	return true;
}

float Xinput_IsAxisX(void)
{
	if (g_state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		// �X�e�B�b�N�̍��������ꂽ
		return (float)g_state.Gamepad.sThumbLX;
	}

	if (g_state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		// �X�e�B�b�N�̍��������ꂽ
		return (float)g_state.Gamepad.sThumbLX;
	}

	return 0.0f;
}

float Xinput_IsAxisY(void)
{
	if (g_state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		// �X�e�B�b�N�̍��������ꂽ
		return (float)g_state.Gamepad.sThumbLY;
	}

	if (g_state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		// �X�e�B�b�N�̍��������ꂽ
		return (float)g_state.Gamepad.sThumbLY;
	}

	return 0.0f;
}