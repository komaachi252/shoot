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
#include "item.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
typedef struct Player_Type_Draw_tag{
	D3DXVECTOR2 position;
	Item_Type type;
	int cut_y;
}Player_Type;

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static const int TEX_TYPE_WIDTH = 214;
static const int TEX_TYPE_HEIGHT = 120;

static const int TYPE_WIDTH = 214.0f;
static const int TYPE_HEIGHT = 30.0f;
static const float TYPE_POS_X = 50.0f;
static const float TYPE_POS_Y = 600.0f;



static const float BULLET_SPEED = 15.0f;
static int tex = 0;

static Player_Type* g_pType;
//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Player_Type_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/normal.png", TEX_TYPE_WIDTH, TEX_TYPE_HEIGHT);
	Texture_Load();

	g_pType = new Player_Type;
	g_pType->type = NORMAL;
	g_pType->cut_y = 0;
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Player_Type_Uninit(void)
{
	delete g_pType;
	g_pType = 0;
	Texture_Destroy(&tex, 1);
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Player_Type_Draw(void)
{
	float tx, ty;
	tx = TYPE_POS_X - TYPE_WIDTH * 0.5f;
	ty = TYPE_POS_Y - TYPE_HEIGHT * 0.5f;
	Sprite_Draw(tex, TYPE_POS_X, TYPE_POS_Y, 0,g_pType->cut_y, TYPE_WIDTH, TYPE_HEIGHT, 0, tx, ty, 1.0f);
}

void Set_Player_Type(Item_Type type)
{
	if (type == SHIELD) { return; }

	g_pType->type = type;
	g_pType->cut_y = type * TYPE_HEIGHT;
}