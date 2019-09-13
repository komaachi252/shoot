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

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������


class Bullet2 {
private:
	float pos_x;
	float pos_y;
	bool is_use;
public:
	//float get_pos_x();
	 
};

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

static int tex = 0;

static const float speed = 15.0f;

static Circle collision;

static Bullet g_Bullets[BULLET_MAX] = {}; //�\���̂Ȃ̂�0�ŏ������ł��Ȃ�

static D3DCOLOR g_color;
//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Bullet_Init(void) 
{
	tex = Texture_SetLoodFile("Asset/Texture/bullet1.png", TEX_BULLET_WIDTH, TEX_BULLET_HEIGHT);
	Texture_Load();
	
	collision.radius = (BULLET_WIDTH / 2);

	for (int i = 0; i < BULLET_MAX; i++) {
		g_Bullets[i].is_used = false;
		g_Bullets[i].collision.radius = (BULLET_WIDTH / 2);
	}
	g_color = D3DCOLOR_RGBA(80, 100, 200, 255);
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Bullet_Uninit(void)
{


}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Bullet_Update(void)
{
	for (int i = 0; i < BULLET_MAX; i++) {
		if (g_Bullets[i].is_used != true) {
			continue;
		}
		g_Bullets[i].x += speed;
		g_Bullets[i].collision.position.x = g_Bullets[i].x;
		g_Bullets[i].collision.position.y = g_Bullets[i].y;
		if (g_Bullets[i].x >= SCREEN_WIDTH + 20.0f) {
			g_Bullets[i].is_used = false;
		}
	}
	//bx += speed;
	//collision.position.x = bx;
	//collision.position.y = by;
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Bullet_Draw(void)
{
	float tx;
	float ty;

	for (int i = 0; i < BULLET_MAX; i++) {
		if (g_Bullets[i].is_used != true) {
			continue;
		}
		tx = g_Bullets[i].x - (BULLET_WIDTH * 0.5f);
		ty = g_Bullets[i].y - (BULLET_HEIGHT * 0.5f);
		Sprite_Draw(tex, tx, ty, BULLET_WIDTH, BULLET_HEIGHT);
		Effect_Create(g_Bullets[i].x, g_Bullets[i].y, g_color, 10);
	}
}

void Bullet_Create(float x, float y)
{
	int i;
	for (i = 0; i < BULLET_MAX; i++) {
		if (g_Bullets[i].is_used != false) {
			continue;
		}
		break;
	}
	if (i >= BULLET_MAX) {
		return;
	}
	g_Bullets[i].is_used = true;
	g_Bullets[i].x = x;
	g_Bullets[i].y = y;
	PlaySound(SOUND_LABEL_SE_NORMAL_SHOT);

}

float get_bullet_width(void)
{
	return BULLET_WIDTH;
}

float get_bullet_height(void)
{
	return BULLET_HEIGHT;
}

bool is_used_bullet(int index)
{
	return g_Bullets[index].is_used;
}

void destroy_bullet(int index)
{
	g_Bullets[index].is_used = false;
}
Circle* bullet_get_collision(int index) // ���g���������Ȃ��A�s�[���ŃR���X�g����
{
	return &g_Bullets[index].collision;
}
