#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "BulletManager.h"
#include "SoundManager.h"
#include "Sprite.h"
#include "TileMap.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram, BulletManager *bulletManager);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	const glm::vec2 sharePosition();
	
private:
	BulletManager *bM;
	SoundManager sound;
	bool bJumping;
	glm::vec2 posPlayer;
	int jumpAngle, startY, lifes;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int cooldown_shot;
};


#endif // _PLAYER_INCLUDE


