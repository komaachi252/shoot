//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	boss�w�b�_[boss.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 9/17(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef BOSS_H_
#define BOSS_H_

#include "collision.h"
#include "item.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define HEAD_HP_MAX (20)
#define BOSS_HP_MAX (1)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
class BOSS_HP{
public:
	static int HEAD_HP;
};
// static �����o�ϐ� �w�b�_

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Boss_Init(void);	//�������֐�
void Boss_Uninit(void);	//�I�������֐�
void Boss_Update(void);	//�X�V����
void Boss_Draw(void);    //�`�揈��
void Boss_Create(void);
bool Boss_Is_Used(void);
void Boss_Destroy(void);
Circle* Boss_get_collision(void);// ���g���������Ȃ��A�s�[���ŃR���X�g����
Square* Boss_get_collision_square(void);
float Boss_Get_Pos_X(void);
float Boss_Get_Pos_Y(void);
void Boss_Sub_HP(Item_Type type);
void Boss_Break(void);
bool Boss_Is_Collision(void);

void Head_Update(void);
void Head_Draw(void);
bool Head_Is_Used(void);
void Head_Destroy(void);
Circle* Head_Get_Collision1(void);// ���g���������Ȃ��A�s�[���ŃR���X�g����
Circle* Head_Get_Collision2(void);// ���g���������Ȃ��A�s�[���ŃR���X�g����
float Head_Get_Pos_X(void);
float Head_Get_Pos_Y(void);
void Head_Sub_HP(Item_Type type);
void Head_Break(void);
bool Head_Is_Collision(void);

#endif
