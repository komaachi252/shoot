//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef SHIELD_H_
#define SHIELD_H_

#include "collision.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Shield_Init(void);	//�������֐�
void Shield_Uninit(void);	//�I�������֐�
void Shield_Update(void);	//�X�V����
void Shield_Draw(void);    //�`�揈��
void Shield_Create(void);
bool is_used_Shield(void);
void Shield_Destroy(void);
Circle* Shield_get_collision(void); // ���g���������Ȃ��A�s�[���ŃR���X�g����

#endif
