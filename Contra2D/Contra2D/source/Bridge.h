#ifndef _BRIDGE_INCLUDE
#define _BRIDGE_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "SoundManager.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Bridge
{
public:
	void init(int length, const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram);
	void render();
	void setTileMap(TileMap *tileMap);
	void update(int deltaTime);

private:
	TileMap *map;
	vector<Sprite> *sprite;
	Texture spritesheet;
};


#endif // _BRIDGE_INCLUDE

