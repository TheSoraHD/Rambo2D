#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bullet.h"

enum directions //0, 1, 2, 3
{
	LEFT, RIGHT, UP, DOWN
};

enum anim
{
	SPREAD, NORMAL
};

void Bullet::createBullet(float posx, float posy, int direction, bool player, ShaderProgram &shaderProgram) {
	dir = direction;
	posBullet = glm::vec2(float(posx), float(posy));
	isPlayer = player;
	spritesheet.loadFromFile("images/bullet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(4, 4), glm::vec2(0.5f, 1.0f), &spritesheet, &shaderProgram);
	//sprite->setNumberAnimations(1);

	//sprite->setAnimationSpeed(NORMAL, 3);
	//sprite->addKeyframe(NORMAL, glm::vec2(0.0f, 0.0f));

	//sprite->changeAnimation(0);

	sprite->setPosition(glm::vec2(float(posBullet.x), float(posBullet.y)));
}

void Bullet::update() {
	if (dir == LEFT) {
		posBullet.x -= 5;
	}
	else if (dir == RIGHT) {
		posBullet.x += 5;
	}
	else if (dir == UP) {
		posBullet.y += 5;
	}
	else if (dir == DOWN) {
		posBullet.y -= 5;
	}
	sprite->setPosition(glm::vec2(float(posBullet.x), float(posBullet.y)));
}

void Bullet::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Bullet::render() {
	sprite->render();
}

Bullet::~Bullet() {
}
