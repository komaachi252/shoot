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
#include "player.h"


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
typedef struct Shield_tag {
	D3DXVECTOR2 position;
	bool is_used;
	Circle collision;
}Shield;

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static const int TEX_SHIELD_WIDTH = 128;
static const int TEX_SHIELD_HEIGHT = 128;

static const float SHIELD_WIDTH = 128.0f;
static const float SHIELD_HEIGHT = 128.0f;

static const float SHIELD_POS_X_DISTANCE = 80.0f;
static int tex = 0;

static Shield* g_pShield;

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Shield_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/shield.png", TEX_SHIELD_WIDTH, TEX_SHIELD_HEIGHT);
	Texture_Load();

	g_pShield = new Shield;

	g_pShield->is_used = false;
	g_pShield->collision.radius = (SHIELD_WIDTH * 0.5f);
	g_pShield->position.y = -SHIELD_HEIGHT;
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Shield_Uninit(void)
{
	delete g_pShield;
	g_pShield = 0;
	Texture_Destroy(&tex, 1);

}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Shield_Update(void)
{
	if (!g_pShield->is_used || !is_used_player()) { return; }

	g_pShield->collision.position.x = g_pShield->position.x = get_player_pos_x() + SHIELD_POS_X_DISTANCE;
	g_pShield->collision.position.y = g_pShield->position.y = get_player_pos_y();
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Shield_Draw(void)
{
	if (!g_pShield->is_used || !is_used_player()) { return; }
	float tx, ty;
	tx = g_pShield->position.x - (SHIELD_WIDTH * 0.5f);
	ty = g_pShield->position.y - (SHIELD_HEIGHT * 0.5f);
	Sprite_Draw(tex, tx, ty, SHIELD_WIDTH, SHIELD_HEIGHT);
}

void Shield_Create(void)
{
	if (g_pShield->is_used) { return; }
	g_pShield->is_used = true;


}

bool is_used_Shield(void)
{
	return g_pShield->is_used;
}

void Shield_Destroy(void)
{
	g_pShield->is_used = false;
}
Circle* Shield_get_collision(void) // ���g���������Ȃ��A�s�[���ŃR���X�g����
{
	return &g_pShield->collision;
}