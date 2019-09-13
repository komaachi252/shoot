//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�V�[������[scene.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 9/10(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
typedef void(*Func)(void);

static const Func INITS[] = {
	Title_Init,
	Game_Init,
	Result_Init,
};

static const Func UNINITS[] = {
	Title_Uninit,
	Game_Uninit,
	Result_Uninit
};

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static SCENE g_Scene = SCENE_TITLE;
static SCENE g_NextScene = SCENE_TITLE;
//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Scene_Init(void)
{
	switch (g_NextScene)
	{
	case SCENE_TITLE:
		Title_Init();
		break;
	case SCENE_GAME:
		Game_Init();
		break;
	case SCENE_RESULT:
		Result_Init();
		break;
	default:
		break;
	}
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Scene_Uninit(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Uninit();
		break;
	case SCENE_GAME:
		Game_Uninit();
		break;
	case SCENE_RESULT:
		Result_Uninit();
		break;
	default:
		break;
	}

}

//��������������������������������������������������������������������������������
//	�X�V����
//��������������������������������������������������������������������������������
void Scene_Update(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Update();
		break;
	case SCENE_GAME:
		Game_Update();
		break;
	case SCENE_RESULT:
		Result_Update();
		break;
	default:
		break;
	}
}

//��������������������������������������������������������������������������������
//	�`�揈��
//��������������������������������������������������������������������������������
void Scene_Draw(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Draw();
		break;
	case SCENE_GAME:
		Game_Draw();
		break;
	case SCENE_RESULT:
		Result_Draw();
		break;
	default:
		break;
	}
}

//��������������������������������������������������������������������������������
//	���̃V�[����\�񂷂鏈��
//��������������������������������������������������������������������������������
void Scene_SetNextScene(SCENE next_scene)
{
	g_NextScene = next_scene;
}

//��������������������������������������������������������������������������������
//  �V�[���؂�ւ�����
//��������������������������������������������������������������������������������
bool Scene_Change(void)
{
	if (g_Scene != g_NextScene) {
		Scene_Uninit();
		if (g_NextScene == SCENE_END) {
			return true;
		}
		Scene_Init();
		g_Scene = g_NextScene;
	}
	return false;
}
