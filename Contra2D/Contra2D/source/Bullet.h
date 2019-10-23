#pragma once
#include "Sprite.h"

class Bullet
{
public:
	void createBullet(float posx , float posy, int direction, bool playe, ShaderProgram &shaderProgram);
	void update();
	~Bullet();

private:
	bool isPlayer;
	glm::vec2 posBullet;
	int dir;
	Texture spritesheet;
	Sprite *sprite;
};

