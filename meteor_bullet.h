//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef METEOR_H_
#define METEOR_H_


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define METEOR_BULLET_MAX (32)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Meteor_Bullet_Init(void);	//�������֐�
void Meteor_Bullet_Uninit(void);	//�I�������֐�
void Meteor_Bullet_Update(void);	//�X�V����
void Meteor_Bullet_Draw(void);    //�`�揈��
void Meteor_Bullet_Create(float x, float y);
bool is_used_Meteor_Bullet(int index);
void Meteor_Bullet_Destroy(int index);
Circle* Meteor_Bullet_get_collision(int index); // ���g���������Ȃ��A�s�[���ŃR���X�g����
float Get_Meteor_Height(void);
#endif
