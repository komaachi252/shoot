//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�e����[bullet.h]
//
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef EFFECT_H_
#define EFFECT_H_


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define EFFECT_MAX (1024)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Effect_Init(void);	// �������֐�
void Effect_Uninit(void); // �I�������֐�
void Effect_Update(void); // �X�V����
void Effect_Draw(void);// �`�揈��
void Effect_Create(float x, float y, D3DCOLOR color, int lifeFrame);
void Effect_Create(float x, float y, D3DCOLOR color, int lifeFrame, float scale); // �G�t�F�N�g�̊g�嗦�������

#endif