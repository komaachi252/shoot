//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
//
//
//	bossヘッダ[boss.h]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                                               作成者 矢吹一俊
//                                                               作成日 9/17(火)
//★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡★彡
#pragma once
#ifndef BOSS_H_
#define BOSS_H_

#include "collision.h"
#include "item.h"

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	定数定義
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
#define HEAD_HP_MAX (20)
#define BOSS_HP_MAX (1)

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	クラス宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
class BOSS_HP{
public:
	static int HEAD_HP;
};
// static メンバ変数 ヘッダ

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
//	プロトタイプ宣言
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
void Boss_Init(void);	//初期化関数
void Boss_Uninit(void);	//終了処理関数
void Boss_Update(void);	//更新処理
void Boss_Draw(void);    //描画処理
void Boss_Create(void);
bool Boss_Is_Used(void);
void Boss_Destroy(void);
Circle* Boss_get_collision(void);// 中身書き換えないアピールでコンストつける
Square* Boss_get_collision_square(void);
float Boss_Get_Pos_X(void);
float Boss_Get_Pos_Y(void);
void Boss_Sub_HP(Item_Type type);
void Boss_Break(void);
bool Boss_Is_Collision(void);

void Head_Update(void);
void Head_Draw(void);
bool Head_Is_Used(void);
void Head_Destroy(void);
Circle* Head_Get_Collision1(void);// 中身書き換えないアピールでコンストつける
Circle* Head_Get_Collision2(void);// 中身書き換えないアピールでコンストつける
float Head_Get_Pos_X(void);
float Head_Get_Pos_Y(void);
void Head_Sub_HP(Item_Type type);
void Head_Break(void);
bool Head_Is_Collision(void);

#endif
