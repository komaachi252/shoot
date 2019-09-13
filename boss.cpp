//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	boss����[boss.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "sprite.h"
#include "texture.h"
#include "common.h"
#include "collision.h"
#include <d3dx9.h>
#include "player.h"
#include "system.h"
#include "ace_boss.h"
#include "item.h"
#include "fade.h"
#include "explosion.h"
#include "rays_enemy.h"
#include "enemy_bullet.h"
#include "score.h"



//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
static const int TEX_BOSS_WIDTH = 512;
static const int TEX_BOSS_HEIGHT = 512;
static const float BOSS_WIDTH = 512.0f;
static const float BOSS_HEIGHT = 512.0f;

static const int TEX_HEAD_WIDTH = 512;
static const int TEX_HEAD_HEIGHT = 512;
static const float HEAD_WIDTH = 512.0f;
static const float HEAD_HEIGHT = 512.0f;

static const float BOSS_START_POS_X = SCREEN_WIDTH * 0.8f;
static const float BOSS_START_POS_Y = -BOSS_HEIGHT;
static const float BOSS_MAX_HP = 30;

static const float BOSS_TO_EYES_POS_X = 1;
static const float BOSS_TO_EYES_POS_Y = 1;
//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
enum BOSS_MODE {
	BOSS_MODE_NONE,
	BOSS_MODE_DEPARTURE,
	BOSS_MODE_TRANSLATE,
	BOSS_MODE_MAX
};


typedef struct BOSS_tag {
	int tex;
	D3DXVECTOR2 position;
	Circle collision;
	bool is_used;
	bool is_collision;
	int hp;
	int angle;
}BOSS;

typedef struct Head_tag {
	int tex;
	D3DXVECTOR2 position;
	Circle coliision1;
	Circle coliision2;
	Circle coliision3;
	bool is_used;
	bool is_collision;
	int hp;
	float alpha;
}Head;


//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ���`
//��������������������������������������������������������������������������������
static BOSS* g_pBoss;
static Head* g_pHead;
//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Boss_Init(void)
{
	g_pBoss = new BOSS;
	g_pBoss->tex = Texture_SetLoodFile("Asset/Texture/oct.png", TEX_BOSS_WIDTH, TEX_BOSS_HEIGHT);
	g_pBoss->is_used = false;
	g_pBoss->is_collision = false;
	g_pHead = new Head;
	g_pHead->tex = Texture_SetLoodFile("Asset/Texture/sea.png", TEX_HEAD_WIDTH, TEX_HEAD_HEIGHT);
	g_pHead->is_used = false;
	g_pHead->is_collision = false;
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Boss_Uninit(void)
{
	Texture_Destroy(&g_pBoss->tex, 1);
	delete g_pBoss;
	Texture_Destroy(&g_pHead->tex, 1);
	delete g_pHead;
}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Boss_Update(void)
{

}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Boss_Draw(void)
{
	if (!g_pBoss->is_used) { return; }
	float tx, ty;
	tx = g_pBoss->position.x - (BOSS_WIDTH * 0.5f);
	ty = g_pBoss->position.y - (BOSS_HEIGHT * 0.5f);
	Sprite_Draw(g_pBoss->tex, tx, ty, BOSS_WIDTH, BOSS_HEIGHT);
}

void Boss_Create(void)
{
	if (g_pBoss->is_used) { return; }
	g_pBoss->is_used = true;
	g_pBoss->is_collision = true;
	g_pBoss->hp = BOSS_MAX_HP;
	g_pBoss->collision.position.x = g_pBoss->position.x = BOSS_START_POS_X;
	g_pBoss->collision.position.y = g_pBoss->position.y = BOSS_START_POS_Y;
	g_pHead->is_used = true;
	g_pHead->is_collision = true;
	g_pHead->position.x = BOSS_START_POS_X + BOSS_TO_EYES_POS_X;
	g_pHead->position.x = BOSS_START_POS_Y + BOSS_TO_EYES_POS_Y;

}

void Head_Update(void)
{

}

void Head_Draw(void)
{
	if (!g_pHead->is_used) { return; }
	float tx, ty;
	tx = g_pHead->position.x - (HEAD_WIDTH * 0.5f);
	ty = g_pHead->position.y - (HEAD_HEIGHT * 0.5f);
	Sprite_DrawAlpha(g_pHead->tex, tx, ty, HEAD_WIDTH, HEAD_HEIGHT, g_pHead->alpha);
}