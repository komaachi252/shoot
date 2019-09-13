//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	����[.cpp]
//
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "texture.h"
#include "sprite.h"
#include "sound.h"
//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
typedef struct EXPLO_tag {
	float x;
	float y;
	int frame;
	bool is_used;
}EXPLOSION;

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������

static int tex;

static const int TEX_EXPLOSION_WIDTH = 512;
static const int TEX_EXPLOSION_HEIGHT = 512;
static const int EXPLOSION_WIDTH = 128;
static const int EXPLOSION_HEIGHT = 128;
static const int EXPLOSION_MAX = 32;
static const int EXPLOSION_FRAME_MAX = 16 * 4;
static int frame_cnt = 0;

static EXPLOSION g_explosion[EXPLOSION_MAX];
//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Explosion_Init(void)
{
	tex = Texture_SetLoodFile("Asset/Texture/bomb.png", TEX_EXPLOSION_WIDTH,TEX_EXPLOSION_HEIGHT);
	Texture_Load();

	frame_cnt = 0;
	
	for (int i = 0; i < EXPLOSION_MAX; i++) {
		g_explosion[i].is_used = false;
	}
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Explosion_Uninit(void)
{


}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Explosion_Update(void)
{
	frame_cnt++;
	for (int i = 0; i < EXPLOSION_MAX; i++) {
		if (!g_explosion[i].is_used) { continue; }
		g_explosion[i].frame++;
		if (g_explosion[i].frame >= EXPLOSION_FRAME_MAX) {
			g_explosion[i].is_used = false;
		}
	}


}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Explosion_Draw(void)
{
	float x;
	float y;

	for (int i = 0; i < EXPLOSION_MAX; i++) {
		if (!g_explosion[i].is_used) { continue; }
		x = g_explosion[i].x - (EXPLOSION_WIDTH / 2);
		y = g_explosion[i].y - (EXPLOSION_HEIGHT / 2);
		Sprite_Draw(tex,x, y, (g_explosion[i].frame / 4) % 4 * EXPLOSION_WIDTH, (g_explosion[i].frame / 4) / 4 * EXPLOSION_HEIGHT, EXPLOSION_WIDTH, EXPLOSION_HEIGHT);
	}

	
}

void Create_Explosion(float x, float y)
{
	int i;
	for (i = 0; i < EXPLOSION_MAX; i++) {
		if (g_explosion[i].is_used) {
			continue;
		}
		break;
	}
	if (i >= EXPLOSION_MAX) { return; }
	g_explosion[i].is_used = true;
	g_explosion[i].frame = 0;
	g_explosion[i].x = x;
	g_explosion[i].y = y;
	PlaySound(SOUND_LABEL_SE_EXPLOSION);
}