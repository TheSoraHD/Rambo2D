#ifndef _BRIDGE_INCLUDE
#define _BRIDGE_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "SoundManager.h"


class Bridge
{
public:
	void init(int length, const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram);
	void render();
	void setPosition(const glm::vec2 &pos);
	void setTileMap(TileMap *tileMap);
	void update(int deltaTime);

private:
	int m_length;
	glm::vec2 posBridge; //position of the first module
	Sprite *sprite;
	Texture spritesheet;
	TileMap *map;
};


#endif // _BRIDGE_INCLUDE

