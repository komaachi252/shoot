//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�G�l�~�[ANEMONES����[anemone.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                                �쐬�� ���r
//                                                                �쐬�� 
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include <d3dx9.h>
#include "collision.h"
#include "sprite.h"
#include "texture.h"
#include "common.h"
#include "enemy_bullet.h"
#include "anemones_enemy.h"
#include "Induction_bullet.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������

typedef struct Anemone_tag {
	D3DXVECTOR2 position;
	Circle collision;
	bool is_used;
	bool bullet_shoot;
	int frame;
}Anemone;

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static int tex;

static const int TEX_ANEMONES_WIDTH = 128;
static const int TEX_ANEMONES_HEIGHT = 64;
static const float ANEMONES_WIDTH = 128.0f;
static const float ANEMONES_HEIGHT = 64.0f;
static const int FRAME_INTERVAL_DIVIDE = 6;
static const int FRME_BULLET_TIME = 120; //�t���[��

static const float ANEMONES_RADIUS = 32.0f;
static const float ANEMONES_SPEED = 4.0f;


static Anemone* g_pAnemones;

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Anemone_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/anemones.png", TEX_ANEMONES_WIDTH, TEX_ANEMONES_HEIGHT);
	Texture_Load();

	g_pAnemones = new Anemone[ANEMONES_MAX];

	for (int i = 0; i < ANEMONES_MAX; i++) {
		(g_pAnemones + i)->is_used = false;
		(g_pAnemones + i)->bullet_shoot = false;
		(g_pAnemones + i)->collision.radius = ANEMONES_RADIUS;

	}
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Anemone_Uninit(void)
{
	delete[] g_pAnemones;
	Texture_Destroy(&tex,1);
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Anemone_Update(void)
{
	for (int i = 0; i < ANEMONES_MAX; i++) {
		if (!(g_pAnemones + i)->is_used) { continue; }
		(g_pAnemones + i)->position.x -= ANEMONES_SPEED;

		(g_pAnemones + i)->frame++;
		if ((g_pAnemones + i)->frame >= FRME_BULLET_TIME && !(g_pAnemones + i)->bullet_shoot) {
			//�e
			Induction_Bullet_Create((g_pAnemones + i)->position.x, (g_pAnemones + i)->position.y - ANEMONES_HEIGHT * 0.5f);
			(g_pAnemones + i)->bullet_shoot = true;
		}
		(g_pAnemones + i)->collision.position.x = (g_pAnemones + i)->position.x;
		(g_pAnemones + i)->collision.position.y = (g_pAnemones + i)->position.y;
	}
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Anemone_Draw(void)
{
	float tx, ty;
	for (int i = 0; i < ANEMONES_MAX; i++) {
		if (!(g_pAnemones + i)->is_used) { continue; }
		tx = (g_pAnemones + i)->position.x - (ANEMONES_WIDTH * 0.5f);
		ty = (g_pAnemones + i)->position.y - (ANEMONES_HEIGHT * 0.5f);
		Sprite_Draw(tex, tx, ty, ANEMONES_WIDTH, ANEMONES_HEIGHT);
	}
}

void Anemones_Create(float x, float y)
{
	int i;
	for (i = 0; i < ANEMONES_MAX; i++) {
		if ((g_pAnemones + i)->is_used) {
			continue;
		}
		break;
	}
	if (i >= ANEMONES_MAX) {
		return;
	}

	(g_pAnemones + i)->is_used = true;
	(g_pAnemones + i)->bullet_shoot = false;
	(g_pAnemones + i)->position.x = x;
	(g_pAnemones + i)->position.y = y;
	(g_pAnemones + i)->collision.position.x = x;
	(g_pAnemones + i)->collision.position.y = y;
	(g_pAnemones + i)->frame = 0;
}

bool is_used_Anemones(int index)
{
	return (g_pAnemones + index)->is_used;
}

void Anemones_Destroy(int index)
{
	(g_pAnemones + index)->is_used = false;
}
Circle* Anemones_Get_Collision(int index) // ���g���������Ȃ��A�s�[���ŃR���X�g����
{
	return &(g_pAnemones + index)->collision;
}

float Get_Anemones_Pos_X(int index)
{
	return (g_pAnemones + index)->position.x;
}

float Get_Anemones_Pos_Y(int index)
{
	return (g_pAnemones + index)->position.y;
}