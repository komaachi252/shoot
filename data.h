//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef DATA_H_
#define DATA_H_

#include <d3dx9.h>

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define  DATA_MAX (4)   // �����f�[�^�� �v�f�R�ԖڂɌ��݂̃v���C���[������

//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
enum Stage_Number {
	STAGE_1,
	STAGE_2,
	STAGE_3
};


//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Data_Init(void);	//�������֐�
void Data_Uninit(void);	//�I�������֐�
void Set_Stage_Number(Stage_Number num);
Stage_Number Get_Stage_Number(void);
void Set_Player_Pos(D3DXVECTOR2 pos);
D3DXVECTOR2 Get_Player_Pos(void);
void Set_Score(int score);
int Get_Score(int i);
int Get_CurrentPlayer(void);  // ���݂̃v���C���[�̗v�f�ԍ����߂�l�ł�
#endif
