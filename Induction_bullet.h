//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef INDUCTION_BULLET_H_
#define INDUCTION_BULLET_H_


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define INDUCTION_MAX (32)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Induction_Bullet_Init(void);	//�������֐�
void Induction_Bullet_Uninit(void);	//�I�������֐�
void Induction_Bullet_Update(void);	//�X�V����
void Induction_Bullet_Draw(void);    //�`�揈��
void Induction_Bullet_Create(float x, float y);
bool is_used_Induction_Bullet(int index);
void Induction_Bullet_Destroy(int index);
Circle* Induction_Bullet_Get_Collision(int index); // ���g���������Ȃ��A�s�[���ŃR���X�g����
void Induction_Bullet_Turn_Over(int index);
bool is_Induction_Turn_Over(int index);
#endif
