#pragma once
#include "Sprite.h"
#include "TileMap.h"

class Bullet
{
public:
	void createBullet(float posx , float posy, int direction, bool spreadGun, int deviation, bool player, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap *tileMap);
	~Bullet();

private:
	int dev;
	bool isPlayer;
	bool spreadBullet;
	glm::vec2 posBullet;
	int dir;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

