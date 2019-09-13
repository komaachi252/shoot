//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�e����[bullet.h]
//
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef ENGINE_H_
#define ENGINE_H_

#include "collision.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define ENGINE_MAX (1024)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Engine_Init(void);	// �������֐�
void Engine_Uninit(void); // �I�������֐�
void Engine_Update(void); // �X�V����
void Engine_Draw(void);// �`�揈��
void Engine_Create(float x, float y, D3DCOLOR color, int lifeFrame);
#endif