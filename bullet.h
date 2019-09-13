//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�e����[bullet.h]
//
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef BULLET_H_
#define BULLET_H_

#include "collision.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define BULLET_MAX (16)

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
enum BulletType {
	Bullet_Normal,
	Bullet_Penetration,
	Bullet_Induction,
};

typedef struct Bullet_tag {
	float x;
	float y;
	Circle collision;
	bool is_used;
	bool is_turn_over;
	//�@��ށ@���x�x�N�g���@
}Bullet;


//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Bullet_Init(void);	// �������֐�
void Bullet_Uninit(void); // �I�������֐�
void Bullet_Update(void); // �X�V����
void Bullet_Draw(void);// �`�揈��

void Bullet_Create(float x, float y);
float get_pos_x(void);
float get_pos_y(void);
float get_bullet_width(void);
float get_bullet_height(void);
bool is_used_bullet(int index);
void destroy_bullet(int index);
Circle_tag* bullet_get_collision(int index);

#endif