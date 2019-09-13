//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef TRIDENT_H_
#define TRIDENT_H_

#include "collision.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define TRIDENT_BULLET_MAX (128)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Trident_Bullet_Init(void);	//�������֐�
void Trident_Bullet_Uninit(void);	//�I�������֐�
void Trident_Bullet_Update(void);	//�X�V����
void Trident_Bullet_Draw(void);    //�`�揈��
void Trident_Bullet_Create(float x, float y);
bool is_used_Trident_Bullet(int index);
void Trident_Bullet_Destroy(int index);
Circle* Trident_Bullet_get_collision(int index); // ���g���������Ȃ��A�s�[���ŃR���X�g����

#endif
