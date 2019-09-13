//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
//
//
//	ƒvƒŒƒCƒ„[ˆ—[player.cpp]
//
//
//šœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœcšœc
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "common.h"
#include "komachi3d.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "bullet.h"
#include "collision.h"
#include "number.h"
#include "item.h"
#include "penetrate_bullet.h"
#include "meteor_bullet.h"
#include "trident_bullet.h"
#include "shield.h"
#include "player.h"
#include "data.h"
#include "sound.h"
#include "gameover.h"
#include "bg.h"

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	’è”’è‹`
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	\‘¢‘ÌéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
typedef struct Player_tag {
	int tex;
	D3DXVECTOR2 position;
	bool is_used;
	Circle collision;
	Item_Type type;
}Player;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒvƒƒgƒ^ƒCƒvéŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™


//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	ƒOƒ[ƒoƒ‹•Ï”éŒ¾
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
static const int TEX_PLAYER_WIDTH = 256;
static const int TEX_PLAYER_HEIGHT = 128;
static const float PLAYER_WIDTH = 256.0f;
static const float PLAYER_HEIGHT = 128.0f;

static const float PLAYER_COLIIW = 157.0f;
static const float PLAYER_COLIIH = 123.0f;

static const float PLAYER_SPEED = 7.0f;
static const float PLAYER_RADIUS = 48.0f;
static const float DISTANCE_TO_MUZLLE_X = 80.0f;
static const float DISTANCE_TO_MUZLLE_Y = 3.0f;

static const float DISTANCE_ENGINE_X = 0.0f;
static const float DISTANCE_ENGINE_Y = 0.0f;
Player* g_player;

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	‰Šú‰»ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Player_Init(void)
{
	g_player = new Player;
	g_player->tex = Texture_SetLoodFile("Asset/Texture/player.png", TEX_PLAYER_WIDTH, TEX_PLAYER_HEIGHT);
	Texture_Load();

	g_player->position.x = PLAYER_POS_X;
	g_player->position.y = PLAYER_POS_Y;
	g_player->is_used = true;
	g_player->collision.radius = PLAYER_RADIUS;
	g_player->type = NORMAL;

}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	I—¹ˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Player_Uninit(void)
{
	Set_Player_Pos(g_player->position);
	Texture_Destroy(&g_player->tex,1);
	delete g_player;
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	XVˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Player_Update(void)
{
	if (!g_player->is_used) {
		return;
	}
	//  ƒvƒŒƒCƒ„[ˆÚ“®
	D3DXVECTOR2 dir(0.0f, 0.0f);

	if (Keyboard_IsPress(DIK_W)) {
		dir.y -= 1.0f;
	}
	if (Keyboard_IsPress(DIK_D)) {
		dir.x += 1.0f;
	}
	if (Keyboard_IsPress(DIK_S)) {
		dir.y += 1.0f;
	}
	if (Keyboard_IsPress(DIK_A)) {
		dir.x -= 1.0f;
	}

	if (g_player->position.y > PLAYER_COLIIH * 0.5f && g_player->position.y < SCREEN_HEIGHT - PLAYER_COLIIH * 0.5f) {
		BG_SetY(dir.y);
	}
	D3DXVec2Normalize(&dir, &dir);

	D3DXVECTOR2 vecSpeed = dir * PLAYER_SPEED;


	g_player->position += vecSpeed;


	g_player->collision.position.x = g_player->position.x;
	g_player->collision.position.y = g_player->position.y;


	g_player->position.x = max(g_player->position.x, PLAYER_COLIIW * 0.5f);
	g_player->position.x = min(g_player->position.x, SCREEN_WIDTH - PLAYER_COLIIW * 0.5f);
	g_player->position.y = min(g_player->position.y, SCREEN_HEIGHT - PLAYER_COLIIH * 0.5f);
	g_player->position.y = max(g_player->position.y, PLAYER_COLIIH * 0.5f);


	switch (g_player->type)
	{
	case NORMAL:
		if (Keyboard_IsTrigger(DIK_SPACE)) {
			Bullet_Create(g_player->position.x + DISTANCE_TO_MUZLLE_X, g_player->position.y + DISTANCE_TO_MUZLLE_Y);
		}
		break;
	case PENETRATE:
		if (Keyboard_IsTrigger(DIK_SPACE)) {
			Penetrate_Bullet_Create(g_player->position.x + DISTANCE_TO_MUZLLE_X, g_player->position.y + DISTANCE_TO_MUZLLE_Y);
		}
		break;
	case METEOR:
		if (Keyboard_IsTrigger(DIK_SPACE)) {
			Meteor_Bullet_Create(g_player->position.x, -Get_Meteor_Height() * 0.5f);
		}
		break;
	case TRIDENT:
		if (Keyboard_IsTrigger(DIK_SPACE)) {
			Trident_Bullet_Create(g_player->position.x + DISTANCE_TO_MUZLLE_X, g_player->position.y + DISTANCE_TO_MUZLLE_Y);
		}
		break;
	default:
		break;
	}
	
}

//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
//	•`‰æˆ—
//™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™
void Player_Draw(void)
{
	if (g_player->is_used == false) {
		return;
	}
	float tx = g_player->position.x - (PLAYER_WIDTH * 0.5f) * PLAYER_SCALE;
	float ty = g_player->position.y - (PLAYER_HEIGHT * 0.5f) * PLAYER_SCALE;
	Sprite_Draw(g_player->tex, tx, ty, PLAYER_WIDTH * PLAYER_SCALE, PLAYER_HEIGHT * PLAYER_SCALE);

}

bool is_used_player(void)
{
	return g_player->is_used;
}

void destroy_player(void)
{
	g_player->is_used = false;
	Game_Over_Create();
}
Circle_tag* player_get_collision(void) // ’†g‘‚«Š·‚¦‚È‚¢ƒAƒs[ƒ‹‚ÅƒRƒ“ƒXƒg‚Â‚¯‚é
{
	return &g_player->collision;
}

float get_player_pos_x(void)
{
	return g_player->position.x;
}

float get_player_pos_y(void)
{
	return g_player->position.y;
}

void Set_Player_Item(Item_Type type)
{
	if (type == SHIELD) {
		//ƒNƒŠƒGƒCƒgƒV[ƒ‹ƒh
		Shield_Create();
		return;
	}
	g_player->type = type;
}

