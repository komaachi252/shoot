//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	�w�b�_[.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               �쐬�� ���r
//                                                               �쐬�� 
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef XINPUT_H_
#define XINPUT_H_


//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#include <d3d9.h>
#include <XInput.h>
//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
bool Xinput_Init(HWND hWnd);	//�������֐�
void Xinput_Uninit(void);	//�I�������֐�
void Xinput_Update(void);	//�X�V����
bool Xinput_IsPress(int key);
bool Xinput_IsTrigger(int key);
bool Xinput_IsExit(int key);
float Xinput_IsAxisX(void);
float Xinput_IsAxisY(void);

#endif
