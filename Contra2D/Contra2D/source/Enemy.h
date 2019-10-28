#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include <glm/glm.hpp>
#include "Sprite.h"
#include "TileMap.h"
#include "SoundManager.h"
#include "Player.h"
#include "BulletManager.h"

class Enemy
{
public:
	void init(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram, Player *target, int typeOf, BulletManager *bulletManager);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void turretAim();
	void turretAnim();

private:

	BulletManager *bM;
	SoundManager sound;
	int typeofEnemy;
	glm::vec2 posEnemy, size;
	Player *player;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

#endif