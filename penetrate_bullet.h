//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef PENETRATE_H_
#define PENETRATE_H_


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define PENETRATE_BULLET_MAX (32)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Penetrate_Init(void);	//�������֐�
void Penetrate_Uninit(void);	//�I�������֐�
void Penetrate_Update(void);	//�X�V����
void Penetrate_Draw(void);    //�`�揈��
void Penetrate_Bullet_Create(float x, float y);
bool is_used_Penetrate_Bullet(int index);
void Penetrate_Bullet_Destroy(int index);
Circle* Penetrate_Bullet_get_collision(int index); // ���g���������Ȃ��A�s�[���ŃR���X�g����

#endif