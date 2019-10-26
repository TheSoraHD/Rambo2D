#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "SoundManager.h"
#include "Player.h"

class Enemy
{
public:
	void init(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram, Player *objetivo);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void turretAim();

private:
	glm::vec2 posEnemy;
	Player *player;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

#endif // _ENEMY_INCLUDE