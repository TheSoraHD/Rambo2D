#ifndef _HUD_INCLUDE
#define _HUD_INCLUDE

#include <glm/glm.hpp>
#include "Sprite.h"
#include "TileMap.h"

class HUD
{
public:

	void init(ShaderProgram &shaderProgram);
	void render();
	void setTileMap(TileMap *tileMap);
	void setPosition(int lifes, bool zawarudo);
	void update(int deltaTime, int lifes, bool zawarudo);


private:
	glm::vec2 posExplosion;
	int timer;
	Texture spritesheet, spritesheet2;
	Sprite *medal1, *medal2, *clock;
	TileMap *map;
};

#endif