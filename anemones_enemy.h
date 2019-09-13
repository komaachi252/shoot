//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef ANEMONE_H_
#define ANEMONE_H_

#include "collision.h"


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define ANEMONES_MAX (32)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Anemone_Init(void);	//�������֐�
void Anemone_Uninit(void);	//�I�������֐�
void Anemone_Update(void);	//�X�V����
void Anemone_Draw(void);    //�`�揈��
void Anemones_Create(float x, float y);
bool is_used_Anemones(int index);
void Anemones_Destroy(int index);
Circle* Anemones_Get_Collision(int index); // ���g���������Ȃ��A�s�[���ŃR���X�g����
float Get_Anemones_Pos_X(int index);
float Get_Anemones_Pos_Y(int index);

#endif
