#pragma once
#include <glm/glm.hpp>
#include "Sprite.h"
#include "TileMap.h"

class Explosion
{
public:
	Explosion();
	~Explosion();

	void init(glm::vec2 pos_explosion, ShaderProgram &shaderProgram);
	void render();
	void setTileMap(TileMap *tileMap);
	void setPosition();
	void update();
	int ret_timer();


private:
	glm::vec2 posExplosion;
	int timer;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

