//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	����[.h]
//
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef COLLI_H_
#define COLLI_H_

#include <d3dx9.h>


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
typedef struct Circle_tag {
	D3DXVECTOR2 position;
	float radius;
}Circle;

typedef struct Square_tag {
	D3DXVECTOR2 position;
	float width;
	float height;
}Square;

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
bool is_collision_circle_circle(Circle *pA,Circle *pB);
bool is_collision_square_square(Square *pA, Square *pB);
#endif