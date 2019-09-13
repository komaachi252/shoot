//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	����[.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "sprite.h"
#include "texture.h"
#include <d3dx9.h>
#include "collision.h"
#include "penetrate_bullet.h"
#include "common.h"
#include "sound.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
typedef struct Penetrate_tag {
	D3DXVECTOR2 position;
	bool is_used;
	Circle collision;
}Penetrate;

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static const int TEX_BULLET_WIDTH = 64;
static const int TEX_BULLET_HEIGHT = 64;

static const float BULLET_WIDTH = 25.0f;
static const float BULLET_HEIGHT = 25.0f;

static const float BULLET_SPEED = 15.0f;
static int tex = 0;

static Penetrate* g_pPenetrate;
//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Penetrate_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/penetrate_bullet.png", TEX_BULLET_WIDTH, TEX_BULLET_HEIGHT);
	Texture_Load();

	g_pPenetrate = new Penetrate[PENETRATE_BULLET_MAX];

	for (int i = 0; i < PENETRATE_BULLET_MAX; i++) {
		(g_pPenetrate + i)->is_used = false;
		(g_pPenetrate + i)->collision.radius = (BULLET_WIDTH * 0.5f);
	}
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Penetrate_Uninit(void)
{
	delete[] g_pPenetrate;
	g_pPenetrate = 0;
	Texture_Destroy(&tex,1);
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Penetrate_Update(void)
{
	for (int i = 0; i < PENETRATE_BULLET_MAX; i++) {
		if (!(g_pPenetrate + i)->is_used) {
			continue;
		}
		(g_pPenetrate + i)->position.x += BULLET_SPEED;
		(g_pPenetrate + i)->collision.position.x = (g_pPenetrate + i)->position.x;
		(g_pPenetrate + i)->collision.position.y = (g_pPenetrate + i)->position.y;
		if ((g_pPenetrate + i)->position.x >= SCREEN_WIDTH + BULLET_WIDTH * 0.5f) {
			(g_pPenetrate + i)->is_used = false;
		}
	}
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Penetrate_Draw(void)
{
	float tx, ty;
	for (int i = 0; i < PENETRATE_BULLET_MAX; i++) {
		if (!(g_pPenetrate + i)->is_used) { continue; }
		tx = (g_pPenetrate + i)->position.x - (BULLET_WIDTH * 0.5f);
		ty = (g_pPenetrate + i)->position.y - (BULLET_HEIGHT * 0.5f);
		Sprite_Draw(tex, tx, ty,BULLET_WIDTH, BULLET_HEIGHT);
	}
}

void Penetrate_Bullet_Create(float x, float y)
{
	int i;
	for (i = 0; i < PENETRATE_BULLET_MAX; i++) {
		if ((g_pPenetrate + i)->is_used != false) {
			continue;
		}
		break;
	}
	if (i >= PENETRATE_BULLET_MAX) { return; }
	(g_pPenetrate + i)->is_used = true;
	(g_pPenetrate + i)->position.x = x;
	(g_pPenetrate + i)->position.y = y;
	PlaySound(SOUND_LABEL_SE_PENETRATE_SHOT);
}

bool is_used_Penetrate_Bullet(int index)
{
	return (g_pPenetrate + index)->is_used;
}

void Penetrate_Bullet_Destroy(int index)
{
	(g_pPenetrate + index)->is_used = false;
}
Circle* Penetrate_Bullet_get_collision(int index) // ���g���������Ȃ��A�s�[���ŃR���X�g����
{
	return &(g_pPenetrate + index)->collision;
}

