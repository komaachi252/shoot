//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	’eˆ—[bullet.h]
//
//
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#pragma once
#ifndef BULLET_H_
#define BULLET_H_

#include "collision.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
#define BULLET_MAX (16)

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒNƒ‰ƒXéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
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
	//@í—Ş@‘¬“xƒxƒNƒgƒ‹@
}Bullet;


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Bullet_Init(void);	// ‰Šú‰»ŠÖ”
void Bullet_Uninit(void); // I—¹ˆ—ŠÖ”
void Bullet_Update(void); // XVˆ—
void Bullet_Draw(void);// •`‰æˆ—

void Bullet_Create(float x, float y);
float get_pos_x(void);
float get_pos_y(void);
float get_bullet_width(void);
float get_bullet_height(void);
bool is_used_bullet(int index);
void destroy_bullet(int index);
Circle_tag* bullet_get_collision(int index);

#endif