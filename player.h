//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
//
//
//   �v���C���[����[player.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   2019.7/16(��)
//���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c���c
#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include "collision.h"
#include "item.h"
//��������������������������������������������������������������������������������
//	�萔��`
//��������������������������������������������������������������������������������
#define PLAYER_POS_X (300.0f)
#define PLAYER_POS_Y (480.0f)
#define PLAYER_SCALE (0.75f)
//��������������������������������������������������������������������������������
//	�N���X�錾
//��������������������������������������������������������������������������������



//��������������������������������������������������������������������������������
//	�v���g�^�C�v�錾
//��������������������������������������������������������������������������������
void Player_Init(void);	//�������֐�
void Player_Uninit(void);	//�I�������֐�
void Player_Update(void);	//�X�V����
void Player_Draw(void);    //�`�揈��

bool is_used_player(void);
void destroy_player(void);
Circle_tag* player_get_collision(void); // ���g���������Ȃ��A�s�[���ŃR���X�g����}
float get_player_pos_x(void);
float get_player_pos_y(void);
void Set_Player_Item(Item_Type type);


#endif