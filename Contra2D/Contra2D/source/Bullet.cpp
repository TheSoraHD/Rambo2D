#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bullet.h"

enum directions //0, 1, 2, 3
{
	LEFT, RIGHT, UP, DOWN, UR, DR, UL, DL
};

enum anim
{
	NORMAL, SPREAD
};

enum SpreadDeviation {
	DEVIATION_1L, DEVIATION_2L, NO_DEVIATION, DEVIATION_1R, DEVIATION_2R
};

void Bullet::createBullet(float posx, float posy, int direction, bool spreadGun, int deviation, bool player, ShaderProgram &shaderProgram) {
	dir = direction;
	posBullet = glm::vec2(float(posx), float(posy));
	isPlayer = player;
	spreadBullet = spreadGun;
	dev = deviation;
	size.x = 8;
	size.y = 8;

	spritesheet.loadFromFile("images/bullet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(0.5f, 1.0f), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(NORMAL, 3);
	sprite->addKeyframe(NORMAL, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(SPREAD, 3);
	sprite->addKeyframe(SPREAD, glm::vec2(0.5f, 0.0f));

	sprite->changeAnimation(0);

	if (spreadBullet) {
		sprite->changeAnimation(SPREAD);
	}

	sprite->setPosition(glm::vec2(float(posBullet.x), float(posBullet.y)));
}

void Bullet::update(int deltaTime) {
	float dev_x = 0;
	switch (dev) {
		case (DEVIATION_1L):
			dev_x = 0.75; break;
		case (DEVIATION_2L):
			dev_x = 1.5; break;
		case (DEVIATION_1R):
			dev_x = -0.75; break;
		case (DEVIATION_2R):
			dev_x = -1.5; break;
	}
	switch (dir) {
		case (LEFT):
			posBullet.x -= 5;
			posBullet.y += (0 + dev_x);
			break;
		case (RIGHT):
			posBullet.x += 5;
			posBullet.y += (0 + dev_x);
			break;
		case (UP):
			posBullet.x += (0 + dev_x);
			posBullet.y -= 5;
			break;
		case (DOWN):
			posBullet.x += (0 + dev_x);
			posBullet.y += 5;
			break;
		case (UR):
			posBullet.x += (2.5 + dev_x);
			posBullet.y -= (2.5 - dev_x);
			break;
		case (DR):
			posBullet.x += (2.5 + dev_x);
			posBullet.y += (2.5 - dev_x);
			break;
		case (UL):
			posBullet.x -= (2.5 + dev_x);
			posBullet.y -= (2.5 - dev_x);
			break;
		case (DL):
			posBullet.x -= (2.5 + dev_x);
			posBullet.y += (2.5 - dev_x);
			break;
	}
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(posBullet.x - map->getScroll()), float(posBullet.y)));
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

glm::vec2 Bullet::ret_pos() {
	return posBullet;
}

glm::vec2 Bullet::ret_size() {
	return size;
}