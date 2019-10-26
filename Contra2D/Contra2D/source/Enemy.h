#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "SoundManager.h"

class Enemy
{
public:
	void init(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

private:
	glm::vec2 posEnemy;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

#endif // _ENEMY_INCLUDE