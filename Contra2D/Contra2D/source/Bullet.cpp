#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bullet.h"

enum directions //0, 1, 2, 3
{
	LEFT, RIGHT, UP, DOWN
};

void Bullet::createBullet(float posx, float posy, int direction, bool player, ShaderProgram &shaderProgram) {
	dir = direction;
	posBullet = glm::vec2(float(posx), float(posy));
	isPlayer = player;
	spritesheet.loadFromFile("images/bullet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(0, 0), &spritesheet, &shaderProgram);
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

Bullet::~Bullet() {
}
