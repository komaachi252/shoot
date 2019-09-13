//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef ACE_BOSS_H_
#define ACE_BOSS_H_

#include "collision.h"
#include "item.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define ACE_MAX_HP (30)
#define NORMAL_BULLET_DAMAGE (1)
#define METEOR_BULLET_DAMAGE (2)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Ace_Init(void);	//�������֐�
void Ace_Uninit(void);	//�I�������֐�
void Ace_Update(void);	//�X�V����
void Ace_Draw(void);    //�`�揈��
void Ace_Create(void);
bool is_used_Ace(void);
void Ace_Destroy(void);
Circle* Ace_get_collision(void);// ���g���������Ȃ��A�s�[���ŃR���X�g����
void Ace_Turn(float y);
float Get_Ace_Pos_X(void);
float Get_Ace_Pos_Y(void);
void Ace_Sub_HP(Item_Type type);
void Ace_Break(void);
bool is_collision_Ace(void);

#endif
