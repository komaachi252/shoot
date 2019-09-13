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
#include "effect.h"
#include "komachi3d.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
typedef struct Effect_tag {
	int lifeFrame;
	int spawnFrame;
	D3DCOLOR color;
	float x;
	float y;
	float scale;
	float subscale;
}Effect;


//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static const int TEX_EFFECT_WIDTH = 80;
static const int TEX_EFFECT_HEIGHT = 80;

static const float EFFECT_WIDTH = 80.0f;
static const float EFFECT_HEIGHT = 80.0f;

static int tex = 0;

static const float speed = 15.0f;


static Effect g_Effects[EFFECT_MAX] = {}; //�\���̂Ȃ̂�0�ŏ������ł��Ȃ�

static int g_EffectFrameCount = 0;

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Effect_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/effect000.jpg", TEX_EFFECT_WIDTH, TEX_EFFECT_HEIGHT);

	g_EffectFrameCount = 0;
	for (int i = 0; i < EFFECT_MAX; i++) {
		g_Effects[i].lifeFrame = 0;
		g_Effects[i].spawnFrame = -1;
		g_Effects[i].scale = 1.0f;
		g_Effects[i].subscale = 0.0f;
	}


}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Effect_Uninit(void)
{


}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Effect_Update(void)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (g_Effects[i].lifeFrame == 0) {
			continue;
		}
		int elapsedFrame = g_EffectFrameCount - g_Effects[i].spawnFrame;
		float e = elapsedFrame / (float)g_Effects[i].lifeFrame;
		// ���͊e�F�����Ə�Z�����

		if (e > 1.0f) {
			e = 1.0f;
			g_Effects[i].lifeFrame = 0;
			g_Effects[i].spawnFrame = -1;
			continue;
		}

		D3DXCOLOR color = g_Effects[i].color;
		color.a = 1.0f - e;
		g_Effects[i].color = color;
		g_Effects[i].scale -= e * g_Effects[i].subscale;


	}
	g_EffectFrameCount++;
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Effect_Draw(void)
{
	float tx;
	float ty;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// �u�����f�B���O����(�f�t�H���g)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		// ���f�X�e�B�l�[�V�����J���[�̎w��(1.0)

	for (int i = 0; i < EFFECT_MAX; i++) {
		if (g_Effects[i].lifeFrame == 0) {
			continue;
		}
		tx = g_Effects[i].x - (EFFECT_WIDTH * 0.5f);
		ty = g_Effects[i].y - (EFFECT_HEIGHT * 0.5f);
		Sprite_SetColor(g_Effects[i].color);
		Sprite_Draw(tex, tx, ty, EFFECT_WIDTH, EFFECT_HEIGHT, 0.0f, 0.0f, 0.0f, g_Effects[i].x, g_Effects[i].y, g_Effects[i].scale);
	}
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// �u�����f�B���O����(�f�t�H���g)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��(1.0 - SRC)
	Sprite_SetColor(0xFFFFFFFF);
}

void Effect_Create(float x, float y, D3DCOLOR color, int lifeFrame) // �G�t�F�N�g�̊g�嗦�������
{

	int i;
	for (i = 0; i < EFFECT_MAX; i++) {
		if (g_Effects[i].lifeFrame > 0) {
			continue;
		}
		break;
	}
	if (i >= EFFECT_MAX) {
		return;
	}
	g_Effects[i].color = color;
	g_Effects[i].x = x;
	g_Effects[i].y = y;
	g_Effects[i].lifeFrame = lifeFrame;
	g_Effects[i].spawnFrame = g_EffectFrameCount;
	//�@�傫��
}

void Effect_Create(float x, float y, D3DCOLOR color, int lifeFrame, float scale) // �G�t�F�N�g�̊g�嗦�������
{

	int i;
	for (i = 0; i < EFFECT_MAX; i++) {
		if (g_Effects[i].lifeFrame > 0) {
			continue;
		}
		break;
	}
	if (i >= EFFECT_MAX) {
		return;
	}
	g_Effects[i].color = color;
	g_Effects[i].x = x;
	g_Effects[i].y = y;
	g_Effects[i].subscale = g_Effects[i].scale = scale;
	g_Effects[i].lifeFrame = lifeFrame;
	//�@�傫��
}
