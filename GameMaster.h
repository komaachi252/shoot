//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef GAME_MASTER_H_
#define GAME_MASTER_H_


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
enum Game_Scene {
	SCENE_NON,
	SCENE_1,
	SCENE_2,
	SCENE_3,
	SCENE_4,
	SCENE_5,
	SCENE_6,
	SCENE_7,
	SCENE_8,
	SCENE_9,
	SCENE_10,
	SCENE_BOSS,
	SCENE_DIS,
};



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Game_Master_Init(void);	//�������֐�
void Game_Master_Uninit(void);	//�I�������֐�
void Game_Master_Update(void);	//�X�V����


#endif
