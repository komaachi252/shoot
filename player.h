//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//   ƒvƒŒƒCƒ„[ˆ—[player.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   2019.7/16(‰Î)
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include "collision.h"
#include "item.h"
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
#define PLAYER_POS_X (300.0f)
#define PLAYER_POS_Y (480.0f)
#define PLAYER_SCALE (0.75f)
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™



//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Player_Init(void);	//‰Šú‰»ŠÖ”
void Player_Uninit(void);	//I—¹ˆ—ŠÖ”
void Player_Update(void);	//XVˆ—
void Player_Draw(void);    //•`‰æˆ—

bool is_used_player(void);
void destroy_player(void);
Circle_tag* player_get_collision(void); // ’†g‘‚«Š·‚¦‚È‚¢ƒAƒs[ƒ‹‚ÅƒRƒ“ƒXƒg‚Â‚¯‚é}
float get_player_pos_x(void);
float get_player_pos_y(void);
void Set_Player_Item(Item_Type type);


#endif