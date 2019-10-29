#ifndef _EXPLOSION_INCLUDE
#define _EXPLOSION_INCLUDE

#include <glm/glm.hpp>
#include "Sprite.h"
#include "TileMap.h"

class Explosion
{
public:

	void init(glm::vec2 pos_explosion, glm::ivec2 size, ShaderProgram &shaderProgram);
	void render();
	void setTileMap(TileMap *tileMap);
	void setPosition();
	void update(int deltaTime);
	int ret_timer();


private:
	glm::vec2 posExplosion;
	int timer;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

#endif