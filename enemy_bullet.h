//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef ENEMY_BULLET_H_
#define ENEMY_BULLET_H_

#include "collision.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define ENEMY_BULLET_MAX (64)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Enemy_Bullet_Init(void);	//�������֐�
void Enemy_Bullet_Uninit(void);	//�I�������֐�
void Enemy_Bullet_Update(void);	//�X�V����
void Enemy_Bullet_Draw(void);    //�`�揈��
void Enemy_Bullet_Create(float x, float y);
bool is_used_Enemy_Bullet(int index);
void Enemy_Bullet_Destroy(int index);
Circle* Enemy_Bullet_Get_Collision(int index); // ���g���������Ȃ��A�s�[���ŃR���X�g����
void Enemy_Bullet_Turn_Over(int index);
bool is_Enemy_Turn_Over(int index);

#endif
