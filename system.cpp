//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//	����[system.cpp]
//
//
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#include <math.h>
#include <d3dx9.h>

//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������


//��������������������������������������������������������������������������������
//	�O���[�o���ϐ��錾
//��������������������������������������������������������������������������������

static float g_sin[360] = {};
static float g_cos[360] = {};
//��������������������������������������������������������������������������������
//	����������
//��������������������������������������������������������������������������������
void System_Init() 
{
	//  �T�C���R�T�C���e�[�u���쐬
	for (int i = 0; i<360; i++) {
		g_sin[i] = (float)sin(i*D3DX_PI / 180);
		g_cos[i] = (float)cos(i*D3DX_PI / 180);
	}
}

//��������������������������������������������������������������������������������
//	���擾
//��������������������������������������������������������������������������������
unsigned GetDigit(unsigned num) 
{
	unsigned digit = 0;

	while(num != 0) {
		num / 10;
		digit++;
	}
	return digit;
}


//��������������������������������������������������������������������������������
//   �p�x�擾
//��������������������������������������������������������������������������������
int GetAngle(float from_x, float from_y, float to_x, float to_y) 
{
	return int(atan2(-double(from_y - to_y), double(from_x - to_x)) / D3DX_PI * 180 + 360) % 360;
}

//��������������������������������������������������������������������������������
//	sin�擾
//��������������������������������������������������������������������������������
float Get_Sin(int angle)
{
	return g_sin[angle];
}

//��������������������������������������������������������������������������������
//	cos�擾
//��������������������������������������������������������������������������������
float Get_Cos(int angle)
{
	return g_cos[angle];
}


