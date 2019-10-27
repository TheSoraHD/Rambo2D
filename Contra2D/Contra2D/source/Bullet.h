#pragma once
#include "Sprite.h"
#include "TileMap.h"

class Bullet
{
public:
	void createBullet(float posx , float posy, int direction, bool playe, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap *tileMap);
	~Bullet();

private:
	bool isPlayer;
	glm::vec2 posBullet;
	int dir;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

