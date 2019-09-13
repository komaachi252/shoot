//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef URCHINS_H_
#define URCHINS_H_

#include "collision.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define URCHINS_MAX (128)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Urchins_Init(void);	//�������֐�
void Urchins_Uninit(void);	//�I�������֐�
void Urchins_Update(void);	//�X�V����
void Urchins_Draw(void);    //�`�揈��
void Urchins_Create(float x, float y);
bool is_used_Urchins(int index);
void Urchins_Destroy(int index);
Circle* Urchins_Get_Collision(int index); // ���g���������Ȃ��A�s�[���ŃR���X�g����
float Get_Urchins_Pos_X(int index);
float Get_Urchins_Pos_Y(int index);




#endif
