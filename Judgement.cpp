//ÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúc
//
//
//	èàóù[.cpp]
//
//
//ÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúcÅöúc
#include "bullet.h"
#include "trident_bullet.h"
#include "meteor_bullet.h"
#include "penetrate_bullet.h"
#include "shield.h"
#include "player.h"
#include "enemy_bullet.h"
#include "Induction_bullet.h"
#include "urchins_enemy.h"
#include "rays_enemy.h"
#include "anemones_enemy.h"
#include "collision.h"
#include "explosion.h"
#include "score.h"
#include "sound.h"
#include "item.h"
#include "playertype_draw.h"
#include "ace_boss.h"
#include "common.h"
#include "boss_hp.h"

#define ITEM_POP_MAX (8)

typedef struct Judge_tag {
	int item_cnt;
	int item_itr;
	Item_Type type;
}Judge;

static void hitCheck_Bullet_isEnemy(void);



//static const int g_ItemPop[ITEM_POP_MAX] = { 6, 4, 5, 4, 4, 6, 5, 4};
static const int g_ItemPop[ITEM_POP_MAX] = {20,21,12,21,22,20,10,21};


static const Item_Type g_Item_Type[ITEM_POP_MAX] = { TRIDENT, PENETRATE, SHIELD, METEOR, TRIDENT, SHIELD, METEOR, PENETRATE};

static Judge* g_pJudge;

void Judgement_Init(void)
{
	g_pJudge = new Judge;
	
	g_pJudge->item_cnt = 0;

	g_pJudge->type = NORMAL;

	g_pJudge->item_itr = 0;
}

void Judgement_Uninit(void)
{
	delete g_pJudge;
	g_pJudge = 0;
}

void Judgement_Update(void)
{
	for (int i = 0; i < BULLET_MAX; i++) {
		for (int j = 0; j < URCHINS_MAX; j++) {
			if (is_used_bullet(i) && is_used_Urchins(j)) {
				if (is_collision_circle_circle(bullet_get_collision(i), Urchins_Get_Collision(j))) {
					Create_Explosion(Get_Urchins_Pos_X(j), Get_Urchins_Pos_Y(j));
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Urchins_Pos_X(j), Get_Urchins_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					destroy_bullet(i);
					Urchins_Destroy(j);
					add_score(get_add_score_num(URCHINS));
				}
			}
		}
	}

	for (int i = 0; i < BULLET_MAX; i++) {
		for (int j = 0; j < RAYS_MAX; j++) {
			if (is_used_bullet(i) && is_used_Rays(j)) {
				if (is_collision_circle_circle(bullet_get_collision(i), Rays_Get_Collision(j))) {
					Create_Explosion(Get_Rays_Pos_X(j), Get_Rays_Pos_Y(j));
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Rays_Pos_X(j), Get_Rays_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					destroy_bullet(i);
					Rays_Destroy(j);
					add_score(get_add_score_num(RAYS));
				}
			}
		}
	}

	for (int i = 0; i < BULLET_MAX; i++) {
		for (int j = 0; j < ANEMONES_MAX; j++) {
			if (is_used_bullet(i) && is_used_Anemones(j)) {
				if (is_collision_circle_circle(bullet_get_collision(i), Anemones_Get_Collision(j))) {
					Create_Explosion(Get_Anemones_Pos_X(j), Get_Anemones_Pos_Y(j));
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Anemones_Pos_X(j), Get_Anemones_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					destroy_bullet(i);
					Anemones_Destroy(j);
					add_score(get_add_score_num(ANEMONES));//enumÇ≈ìoò^
				}
			}
		}
	}
	for (int i = 0; i < BULLET_MAX; i++) {
		if (is_used_bullet(i) && is_collision_Ace()) {
			if (is_collision_circle_circle(bullet_get_collision(i), Ace_get_collision())) {
				//PlaySound(SOUND_LABEL_SE_EXPLOSION);
				destroy_bullet(i);
				Ace_Sub_HP(NORMAL);
				Sub_Boss_HP(NORMAL);
				PlaySound(SOUND_LABEL_SE_DAMAGE);
			}
		}
	}

	//ä—í íe
	for (int i = 0; i < PENETRATE_BULLET_MAX; i++) {
		for (int j = 0; j < URCHINS_MAX; j++) {
			if (is_used_Penetrate_Bullet(i) && is_used_Urchins(j)) {
				if (is_collision_circle_circle(Penetrate_Bullet_get_collision(i), Urchins_Get_Collision(j))) {
					Create_Explosion(Get_Urchins_Pos_X(j), Get_Urchins_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Urchins_Pos_X(j), Get_Urchins_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Urchins_Destroy(j);
					add_score(get_add_score_num(URCHINS));
				}
			}
		}
	}

	for (int i = 0; i < PENETRATE_BULLET_MAX; i++) {
		for (int j = 0; j < RAYS_MAX; j++) {
			if (is_used_Penetrate_Bullet(i) && is_used_Rays(j)) {
				if (is_collision_circle_circle(Penetrate_Bullet_get_collision(i), Rays_Get_Collision(j))) {
					Create_Explosion(Get_Rays_Pos_X(j), Get_Rays_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Rays_Pos_X(j), Get_Rays_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Rays_Destroy(j);
					add_score(get_add_score_num(RAYS));
				}
			}
		}
	}

	for (int i = 0; i < PENETRATE_BULLET_MAX; i++) {
		for (int j = 0; j < ANEMONES_MAX; j++) {
			if (is_used_Penetrate_Bullet(i) && is_used_Anemones(j)) {
				if (is_collision_circle_circle(Penetrate_Bullet_get_collision(i), Anemones_Get_Collision(j))) {
					Create_Explosion(Get_Anemones_Pos_X(j), Get_Anemones_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Anemones_Pos_X(j), Get_Anemones_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Anemones_Destroy(j);
					add_score(get_add_score_num(ANEMONES));//enumÇ≈ìoò^
				}
			}
		}
	}
	for (int i = 0; i < PENETRATE_BULLET_MAX; i++) {
		if (is_used_Penetrate_Bullet(i) && is_collision_Ace()) {
			if (is_collision_circle_circle(Penetrate_Bullet_get_collision(i), Ace_get_collision())) {
				//PlaySound(SOUND_LABEL_SE_EXPLOSION);
				Penetrate_Bullet_Destroy(i);
				Ace_Sub_HP(PENETRATE);
				Sub_Boss_HP(PENETRATE);
				PlaySound(SOUND_LABEL_SE_DAMAGE);
			}
		}
	}
	//ÉgÉâÉCÉfÉìÉg
	for (int i = 0; i < TRIDENT_BULLET_MAX; i++) {
		for (int j = 0; j < URCHINS_MAX; j++) {
			if (is_used_Trident_Bullet(i) && is_used_Urchins(j)) {
				if (is_collision_circle_circle(Trident_Bullet_get_collision(i), Urchins_Get_Collision(j))) {
					Create_Explosion(Get_Urchins_Pos_X(j), Get_Urchins_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Urchins_Pos_X(j), Get_Urchins_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Trident_Bullet_Destroy(i);
					Urchins_Destroy(j);
					add_score(get_add_score_num(URCHINS));
				}
			}
		}
	}
	for (int i = 0; i < TRIDENT_BULLET_MAX; i++) {
		for (int j = 0; j < RAYS_MAX; j++) {
			if (is_used_Trident_Bullet(i) && is_used_Rays(j)) {
				if (is_collision_circle_circle(Trident_Bullet_get_collision(i), Rays_Get_Collision(j))) {
					Create_Explosion(Get_Rays_Pos_X(j), Get_Rays_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Rays_Pos_X(j), Get_Rays_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Trident_Bullet_Destroy(i);
					Rays_Destroy(j);
					add_score(get_add_score_num(RAYS));
				}
			}
		}
	}
	for (int i = 0; i < TRIDENT_BULLET_MAX; i++) {
		for (int j = 0; j < ANEMONES_MAX; j++) {
			if (is_used_Trident_Bullet(i) && is_used_Anemones(j)) {
				if (is_collision_circle_circle(Trident_Bullet_get_collision(i), Anemones_Get_Collision(j))) {
					Create_Explosion(Get_Anemones_Pos_X(j), Get_Anemones_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Anemones_Pos_X(j), Get_Anemones_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Trident_Bullet_Destroy(i);
					Anemones_Destroy(j);
					add_score(get_add_score_num(ANEMONES));//enumÇ≈ìoò^
				}
			}
		}
	}
	for (int i = 0; i < TRIDENT_BULLET_MAX; i++) {
		if (is_used_Trident_Bullet(i) && is_collision_Ace()) {
			if (is_collision_circle_circle(Trident_Bullet_get_collision(i), Ace_get_collision())) {
				Trident_Bullet_Destroy(i);
				Ace_Sub_HP(TRIDENT);
				Sub_Boss_HP(TRIDENT);
				PlaySound(SOUND_LABEL_SE_DAMAGE);
			}
		}
	}
	//ÉÅÉeÉI
	for (int i = 0; i < METEOR_BULLET_MAX; i++) {
		for (int j = 0; j < URCHINS_MAX; j++) {
			if (is_used_Meteor_Bullet(i) && is_used_Urchins(j)) {
				if (is_collision_circle_circle(Meteor_Bullet_get_collision(i), Urchins_Get_Collision(j))) {
					Create_Explosion(Get_Urchins_Pos_X(j), Get_Urchins_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Urchins_Pos_X(j), Get_Urchins_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Meteor_Bullet_Destroy(i);
					Urchins_Destroy(j);
					add_score(get_add_score_num(URCHINS));
				}
			}
		}
	}
	for (int i = 0; i < METEOR_BULLET_MAX; i++) {
		for (int j = 0; j < RAYS_MAX; j++) {
			if (is_used_Meteor_Bullet(i) && is_used_Rays(j)) {
				if (is_collision_circle_circle(Meteor_Bullet_get_collision(i), Rays_Get_Collision(j))) {
					Create_Explosion(Get_Rays_Pos_X(j), Get_Rays_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Rays_Pos_X(j), Get_Rays_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Meteor_Bullet_Destroy(i);
					Rays_Destroy(j);
					add_score(get_add_score_num(RAYS));
				}
			}
		}
	}
	for (int i = 0; i < METEOR_BULLET_MAX; i++) {
		for (int j = 0; j < ANEMONES_MAX; j++) {
			if (is_used_Meteor_Bullet(i) && is_used_Anemones(j)) {
				if (is_collision_circle_circle(Meteor_Bullet_get_collision(i), Anemones_Get_Collision(j))) {
					Create_Explosion(Get_Anemones_Pos_X(j), Get_Anemones_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Anemones_Pos_X(j), Get_Anemones_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Meteor_Bullet_Destroy(i);
					Anemones_Destroy(j);
					add_score(get_add_score_num(ANEMONES));//enumÇ≈ìoò^
				}
			}
		}
	}
	for (int i = 0; i < METEOR_BULLET_MAX; i++) {
		if (is_used_Meteor_Bullet(i) && is_collision_Ace()) {
			if (is_collision_circle_circle(Meteor_Bullet_get_collision(i), Ace_get_collision())) {
				Meteor_Bullet_Destroy(i);
				Ace_Sub_HP(METEOR);
				Sub_Boss_HP(METEOR);
				PlaySound(SOUND_LABEL_SE_DAMAGE);
			}
		}
	}

	//ÉGÉlÉ~Å[êQï‘ÇË
	for (int i = 0; i < ENEMY_BULLET_MAX; i++) {
		for (int j = 0; j < URCHINS_MAX; j++) {
			if (is_used_Enemy_Bullet(i) && is_used_Urchins(j) && is_Enemy_Turn_Over(i)) {
				if (is_collision_circle_circle(Enemy_Bullet_Get_Collision(i), Urchins_Get_Collision(j))) {
					Create_Explosion(Get_Urchins_Pos_X(j), Get_Urchins_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Urchins_Pos_X(j), Get_Urchins_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Enemy_Bullet_Destroy(i);
					Urchins_Destroy(j);
					add_score(get_add_score_num(URCHINS));
				}
			}
		}
	}
	for (int i = 0; i < ENEMY_BULLET_MAX; i++) {
		for (int j = 0; j < RAYS_MAX; j++) {
			if (is_used_Enemy_Bullet(i) && is_used_Rays(j) && is_Enemy_Turn_Over(i)) {
				if (is_collision_circle_circle(Enemy_Bullet_Get_Collision(i), Rays_Get_Collision(j))) {
					Create_Explosion(Get_Rays_Pos_X(j), Get_Rays_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Rays_Pos_X(j), Get_Rays_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Enemy_Bullet_Destroy(i);
					Rays_Destroy(j);
					add_score(get_add_score_num(RAYS));
				}
			}
		}
	}
	for (int i = 0; i < ENEMY_BULLET_MAX; i++) {
		for (int j = 0; j < ANEMONES_MAX; j++) {
			if (is_used_Enemy_Bullet(i) && is_used_Anemones(j) && is_Enemy_Turn_Over(i)) {
				if (is_collision_circle_circle(Enemy_Bullet_Get_Collision(i), Anemones_Get_Collision(j))) {
					Create_Explosion(Get_Anemones_Pos_X(j), Get_Anemones_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Anemones_Pos_X(j), Get_Anemones_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Enemy_Bullet_Destroy(i);
					Anemones_Destroy(j);
					add_score(get_add_score_num(ANEMONES));//enumÇ≈ìoò^
				}
			}
		}
	}

	//óUì±êQï‘ÇË

	for (int i = 0; i < INDUCTION_MAX; i++) {
		for (int j = 0; j < URCHINS_MAX; j++) {
			if (is_used_Induction_Bullet(i) && is_used_Urchins(j) && is_Induction_Turn_Over(i)) {
				if (is_collision_circle_circle(Induction_Bullet_Get_Collision(i), Urchins_Get_Collision(j))) {
					Create_Explosion(Get_Urchins_Pos_X(j), Get_Urchins_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Urchins_Pos_X(j), Get_Urchins_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Induction_Bullet_Destroy(i);
					Urchins_Destroy(j);
					add_score(get_add_score_num(URCHINS));
				}
			}
		}
	}
	for (int i = 0; i < INDUCTION_MAX; i++) {
		for (int j = 0; j < RAYS_MAX; j++) {
			if (is_used_Induction_Bullet(i) && is_used_Rays(j) && is_Induction_Turn_Over(i)) {
				if (is_collision_circle_circle(Induction_Bullet_Get_Collision(i), Rays_Get_Collision(j))) {
					Create_Explosion(Get_Rays_Pos_X(j), Get_Rays_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Rays_Pos_X(j), Get_Rays_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Induction_Bullet_Destroy(i);
					Rays_Destroy(j);
					add_score(get_add_score_num(RAYS));
				}
			}
		}
	}
	for (int i = 0; i < INDUCTION_MAX; i++) {
		for (int j = 0; j < ANEMONES_MAX; j++) {
			if (is_used_Induction_Bullet(i) && is_used_Anemones(j) && is_Induction_Turn_Over(i)) {
				if (is_collision_circle_circle(Induction_Bullet_Get_Collision(i), Anemones_Get_Collision(j))) {
					Create_Explosion(Get_Anemones_Pos_X(j), Get_Anemones_Pos_Y(j));
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
					g_pJudge->item_cnt++;
					if (g_pJudge->item_cnt >= g_ItemPop[g_pJudge->item_itr]) {
						Item_Create(g_Item_Type[g_pJudge->item_itr], Get_Anemones_Pos_X(j), Get_Anemones_Pos_Y(j));
						g_pJudge->item_cnt = 0;
						g_pJudge->item_itr++;
						if (g_pJudge->item_itr >= ITEM_POP_MAX) { g_pJudge->item_itr = 0; }
					}
					Induction_Bullet_Destroy(i);
					Anemones_Destroy(j);
					add_score(get_add_score_num(ANEMONES));//enumÇ≈ìoò^
				}
			}
		}
	}


	//ÉVÅ[ÉãÉh

	for (int i = 0; i < ENEMY_BULLET_MAX; i++) {
		if (is_used_Shield() && is_used_Enemy_Bullet(i)) {
			if (is_collision_circle_circle(Shield_get_collision(), Enemy_Bullet_Get_Collision(i))) {
				Enemy_Bullet_Turn_Over(i);
				Shield_Destroy();
				PlaySound(SOUND_LABEL_SE_REFLECT);
			}
		}
	}
	for (int i = 0; i < INDUCTION_MAX; i++) {
		if (is_used_Shield() && is_used_Induction_Bullet(i)) {
			if (is_collision_circle_circle(Shield_get_collision(), Induction_Bullet_Get_Collision(i))) {
				//Induction_Bullet_Destroy(i);
				Induction_Bullet_Turn_Over(i);
				Shield_Destroy();
				PlaySound(SOUND_LABEL_SE_REFLECT);
			}
		}
	}
	for (int i = 0; i < URCHINS_MAX; i++) {
		if (is_used_Shield() && is_used_Urchins(i)) {
			if (is_collision_circle_circle(Shield_get_collision(), Urchins_Get_Collision(i))) {
				Create_Explosion(Get_Urchins_Pos_X(i), Get_Urchins_Pos_Y(i));
				Shield_Destroy();
				Urchins_Destroy(i);
				PlaySound(SOUND_LABEL_SE_REFLECT);
			}
		}
	}
	for (int i = 0; i < RAYS_MAX; i++) {
		if (is_used_Shield() && is_used_Rays(i)) {
			if (is_collision_circle_circle(Shield_get_collision(), Rays_Get_Collision(i))) {
				Create_Explosion(Get_Rays_Pos_X(i), Get_Rays_Pos_Y(i));
				Shield_Destroy();
				Rays_Destroy(i);
				PlaySound(SOUND_LABEL_SE_REFLECT);
			}
		}
	}
	for (int i = 0; i < ANEMONES_MAX; i++) {
		if (is_used_Shield() && is_used_Anemones(i)) {
			if (is_collision_circle_circle(Shield_get_collision(), Anemones_Get_Collision(i))) {
				Create_Explosion(Get_Anemones_Pos_X(i), Get_Anemones_Pos_Y(i));
				Shield_Destroy();
				Anemones_Destroy(i);
				PlaySound(SOUND_LABEL_SE_REFLECT);
			}
		}
	}
	if (is_used_Shield() && is_used_Ace()) {
		if (is_collision_circle_circle(Shield_get_collision(), Ace_get_collision())) {
			Shield_Destroy();
			PlaySound(SOUND_LABEL_SE_REFLECT);
			Ace_Sub_HP(NORMAL);
			Sub_Boss_HP(NORMAL);
		}
	}





	
	for (int i = 0; i < URCHINS_MAX; i++) {
		if (is_used_player() && is_used_Urchins(i)) {
			if (is_collision_circle_circle(player_get_collision(), Urchins_Get_Collision(i))) {
				Create_Explosion(Get_Urchins_Pos_X(i), Get_Urchins_Pos_Y(i));
				Create_Explosion(get_player_pos_x(), get_player_pos_y());
				destroy_player();
				Urchins_Destroy(i);
			}
		}
	}
	for (int i = 0; i < RAYS_MAX; i++) {
		if (is_used_player() && is_used_Rays(i)) {
			if (is_collision_circle_circle(player_get_collision(), Rays_Get_Collision(i))) {
				Create_Explosion(Get_Rays_Pos_X(i), Get_Rays_Pos_Y(i));
				Create_Explosion(get_player_pos_x(), get_player_pos_y());
				destroy_player();
				Rays_Destroy(i);
			}
		}
	}
	for (int i = 0; i < ANEMONES_MAX; i++) {
		if (is_used_player() && is_used_Anemones(i)) {
			if (is_collision_circle_circle(player_get_collision(), Anemones_Get_Collision(i))) {
				Create_Explosion(Get_Anemones_Pos_X(i), Get_Anemones_Pos_Y(i));
				Create_Explosion(get_player_pos_x(), get_player_pos_y());
				destroy_player();
				Anemones_Destroy(i);
			}
		}
	}

	if (is_used_player() && is_collision_Ace()) {
		if (is_collision_circle_circle(player_get_collision(), Ace_get_collision())) {
			Create_Explosion(get_player_pos_x(), get_player_pos_y());
			destroy_player();
		}
	}


	for (int i = 0; i < ENEMY_BULLET_MAX; i++) {
		if (is_used_player() && is_used_Enemy_Bullet(i)) {
			if (is_collision_circle_circle(player_get_collision(), Enemy_Bullet_Get_Collision(i))) {
				Create_Explosion(get_player_pos_x(), get_player_pos_y());
				destroy_player();
				Enemy_Bullet_Destroy(i);
			}
		}
	}
	for (int i = 0; i < INDUCTION_MAX; i++) {
		if (is_used_player() && is_used_Induction_Bullet(i) && !is_Induction_Turn_Over(i)) {
			if (is_collision_circle_circle(player_get_collision(), Induction_Bullet_Get_Collision(i))) {
				Create_Explosion(get_player_pos_x(), get_player_pos_y());
				destroy_player();
				Induction_Bullet_Destroy(i);
			}
		}
	}

	for (int i = 0; i < ITEM_MAX; i++) {
		if (is_used_player() && is_used_Item(i)) {
			if (is_collision_circle_circle(player_get_collision(), Item_Get_Collision(i))) {
				Item_Destroy(i);
				if (Get_Item_Type(i) != SHIELD) {
					g_pJudge->type = Get_Item_Type(i);
				}
				Set_Player_Item(Get_Item_Type(i));
				Set_Player_Type(Get_Item_Type(i));
				PlaySound(SOUND_LABEL_SE_ITEM);
			}
		}
	}

	int mini = SCREEN_WIDTH;
	float ey;
	bool is_enemy = false;
	for (int i = 0; i < URCHINS_MAX; i++) {
		if (is_used_Ace() && is_used_Urchins(i)) {
			if (mini > Get_Ace_Pos_X() - Get_Urchins_Pos_X(i) && Get_Urchins_Pos_X(i) - Get_Ace_Pos_X() > 0) {
				mini = Get_Ace_Pos_X() - Get_Urchins_Pos_X(i);
				ey = Get_Urchins_Pos_Y(i);
				is_enemy = true;
			}
		}
	}
	for (int i = 0; i < RAYS_MAX; i++) {
		if (is_used_Ace() && is_used_Rays(i)) {
			if (mini > Get_Ace_Pos_X() - Get_Rays_Pos_X(i) && Get_Rays_Pos_X(i) - Get_Ace_Pos_X() > 0) {
				mini = Get_Ace_Pos_X() - Get_Rays_Pos_X(i);
				ey = Get_Rays_Pos_Y(i);
				is_enemy = true;
			}
		}
	}
	for (int i = 0; i < ANEMONES_MAX; i++) {
		if (is_used_Ace() && is_used_Anemones(i)) {
			if (mini > Get_Ace_Pos_X() - Get_Anemones_Pos_X(i) && Get_Anemones_Pos_X(i) - Get_Ace_Pos_X() > 0) {
				mini = Get_Ace_Pos_X() - Get_Anemones_Pos_X(i);
				ey = Get_Anemones_Pos_Y(i);
				is_enemy = true;
			}
		}
	}
	if (is_enemy) {
		Ace_Turn(ey);
	}

}

