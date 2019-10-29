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
	void movement();
	glm::vec2 ret_size();
	glm::vec2 ret_pos();
	void activateSpread(bool powerUp);
	void hit();
	bool ret_hurt();
	bool game_over();
	bool isgod();
	void render();
	
	void setTileMap(TileMap *tileMap);
	void second_level_mode(bool status);
	void setPosition(const glm::vec2 &pos);
	const glm::vec2 sharePosition();
	
private:
	BulletManager *bM;
	SoundManager sound;
	bool bJumping, spreadGun, left, hurt, second_level;
	glm::vec2 posPlayer, size;
	int jumpAngle, startY, lifes;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int cooldown_shot, cooldown_dead;
	int god_mode;
};


#endif // _PLAYER_INCLUDE


