//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	����[data.cpp]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#define _CRT_SECURE_NO_WARNINGS
#include "data.h"
#include <d3dx9.h>
#include "stdio.h"

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������
typedef struct Data_tag {
	int score;
	bool currentplayer;
	Stage_Number stage_num;
	D3DXVECTOR2 player_pos;
}Data;

//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������
static Data* g_pData;

//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void Data_Init(void)
{
	g_pData = new Data[DATA_MAX];
	g_pData->score = 0;
	for (int i = 0; i < DATA_MAX; i++) {
		(g_pData + i)->score = 0;
		(g_pData + i)->stage_num = STAGE_1;
		(g_pData + i)->player_pos.x = 1.0f;
		(g_pData + i)->player_pos.y = 1.0f;
		(g_pData + i)->currentplayer = false;
	}
	(g_pData + DATA_MAX - 1)->currentplayer = true;
	FILE *fp;

	if ((fp = fopen("���[�ԂŁ[��.dat", "rb")) != NULL) {
		for (int i = 0; i < DATA_MAX - 1; i++) {
			fread(g_pData + i, sizeof(Data), 1, fp);
		}
	}
	//fclose(fp);
}

//��������������������������������������������������������������������������������
//	�I������
//��������������������������������������������������������������������������������
void Data_Uninit(void)
{
	FILE *fp = fopen("���[�ԂŁ[��.dat", "wb");

	for (int i = 0; i < DATA_MAX - 1; i++) {
		fwrite(g_pData + i, sizeof(Data), 1, fp);
	}
	fclose(fp);
	delete g_pData;
	g_pData = 0;
}

//��������������������������������������������������������������������������������
//	�X�e�[�W�ԍ��ݒ�
//��������������������������������������������������������������������������������
void Set_Stage_Number(Stage_Number num) 
{
	(g_pData + DATA_MAX - 1)->stage_num = num;
}

Stage_Number Get_Stage_Number(void)
{
	return (g_pData + DATA_MAX - 1)->stage_num;
}

void Set_Player_Pos(D3DXVECTOR2 pos)
{
	(g_pData + DATA_MAX - 1)->player_pos = pos;
}

D3DXVECTOR2 Get_Player_Pos(void)
{
	return (g_pData + DATA_MAX - 1)->player_pos;
}

void Set_Score(int score)
{
	(g_pData + DATA_MAX - 1)->score = score;

    //  �\�[�g
	int itr = DATA_MAX - 1;
	for (int i = DATA_MAX - 2; i >= 0; i--) {
		if ((g_pData + DATA_MAX - 1)->score >= (g_pData + i)->score) {
			itr = i;
		}
	}
	if (itr == DATA_MAX - 1) {
		return;
	}
	int w;
	w = (g_pData + itr)->score;
	(g_pData + itr)->score = (g_pData + DATA_MAX - 1)->score;
	(g_pData + DATA_MAX - 1)->score = w;

	bool current;
	current = (g_pData + itr)->currentplayer;
	(g_pData + itr)->currentplayer = (g_pData + DATA_MAX - 1)->currentplayer;
	(g_pData + DATA_MAX - 1)->score = current;

}

int Get_Score(int i)
{
	return i < DATA_MAX ? (g_pData + i)->score : -1;
}

int Get_CurrentPlayer(void)
{
	int i;
	for (i = 0; i < DATA_MAX; i++) {
		if ((g_pData + i)->currentplayer) {
			break;
		}
	}
	return i;
}
