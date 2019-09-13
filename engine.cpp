//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�e����[bullet.cpp]
//
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "sprite.h"
#include "texture.h"
#include "player.h"
#include "common.h"
#include "collision.h"
#include "bullet.h"
#include "sound.h"
#include "engine.h"
#include "komachi3d.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
typedef struct Engine_tag {
	int lifeFrame;
	int spawnFrame;
	D3DCOLOR color;
	float x;
	float y;
	float scale;
}Engine;


//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static const int TEX_ENGINE_WIDTH = 80;
static const int TEX_ENGINE_HEIGHT = 80;

static const float ENGINE_WIDTH = 10.0f;
static const float ENGINE_HEIGHT = 10.0f;

static int tex = 0;

static int g_EffectFrameCount = 0;

static Engine* g_pEngine;

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Engine_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/effect000.jpg", TEX_ENGINE_WIDTH, TEX_ENGINE_HEIGHT);

	g_pEngine = new Engine[ENGINE_MAX];

	g_EffectFrameCount = 0;
	for (int i = 0; i < ENGINE_MAX; i++) {
		(g_pEngine + i)->lifeFrame = 0;
		(g_pEngine + i)->spawnFrame = -1;
		(g_pEngine + i)->scale = 1.0f;
	}


}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Engine_Uninit(void)
{
	delete[] g_pEngine;
	g_pEngine = 0;

}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Engine_Update(void)
{
	for (int i = 0; i < ENGINE_MAX; i++) {
		if ((g_pEngine + i)->lifeFrame == 0) {
			continue;
		}
		int elapsedFrame = g_EffectFrameCount - (g_pEngine + i)->spawnFrame;
		float e = elapsedFrame / (float)(g_pEngine + i)->lifeFrame;
		// ���͊e�F�����Ə�Z�����

		if (e > 1.0f) {
			e = 1.0f;
			(g_pEngine + i)->lifeFrame = 0;
			(g_pEngine + i)->spawnFrame = -1;
			continue;
		}

		D3DXCOLOR color = (g_pEngine + i)->color;
		color.a = 1.0f - e;
		(g_pEngine + i)->color = color;
	}
	g_EffectFrameCount++;
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Engine_Draw(void)
{
	float tx;
	float ty;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// �u�����f�B���O����(�f�t�H���g)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		// ���f�X�e�B�l�[�V�����J���[�̎w��(1.0)

	for (int i = 0; i < ENGINE_MAX; i++) {
		if ((g_pEngine + i)->lifeFrame == 0) {
			continue;
		}
		tx = (g_pEngine + i)->x - (ENGINE_WIDTH * 0.5f);
		ty = (g_pEngine + i)->y - (ENGINE_HEIGHT * 0.5f);
		Sprite_SetColor((g_pEngine + i)->color);
		Sprite_Draw(tex, tx, ty, ENGINE_WIDTH, ENGINE_HEIGHT);
	}
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// �u�����f�B���O����(�f�t�H���g)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��(1.0 - SRC)
	Sprite_SetColor(0xFFFFFFFF);
}

void Engine_Create(float x, float y, D3DCOLOR color, int lifeFrame) // �G�t�F�N�g�̊g�嗦�������
{

	int i;
	for (i = 0; i < ENGINE_MAX; i++) {
		if ((g_pEngine + i)->lifeFrame > 0) {
			continue;
		}
		break;
	}
	if (i >= ENGINE_MAX) {
		return;
	}
	(g_pEngine + i )->color = color;
	(g_pEngine + i )->x = x;
	(g_pEngine + i )->y = y;
	(g_pEngine + i )->lifeFrame = lifeFrame;
	(g_pEngine + i )->spawnFrame = g_EffectFrameCount;
	//�@�傫��
}
