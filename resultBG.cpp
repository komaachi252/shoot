//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	����[.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "texture.h"
#include "sprite.h"


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static int tex1;
static int tex2;
static int tex3;

static const int BG_WIDTH = 1280;
static const int BG_HEIGHT = 720;

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Result_BG_Init(void)
{
	tex1 = Texture_SetLoodFile("Asset/Texture/space1.png", BG_WIDTH, BG_HEIGHT);
	tex2 = Texture_SetLoodFile("Asset/Texture/space2.png", BG_WIDTH, BG_HEIGHT);
	tex3 = Texture_SetLoodFile("Asset/Texture/space3.png", BG_WIDTH, BG_HEIGHT);
	Texture_Load();

}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Result_BG_Uninit(void)
{


}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Result_BG_Update(void)
{

}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Result_BG_Draw(void)
{
	Sprite_Draw(tex1,0.0f,0.0f);
	Sprite_Draw(tex2,0.0f,0.0f);
	Sprite_Draw(tex3,0.0f,0.0f);
}
