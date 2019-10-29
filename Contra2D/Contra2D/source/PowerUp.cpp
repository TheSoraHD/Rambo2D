#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "PowerUp.h"

enum animPowerUp {
	DEFAULT
};

void PowerUp::init(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram) {
	spritesheet.loadFromFile("images/powerup2x.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(1.0f, 1.0f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	size.x = 50;
	size.y = 45;
	sprite->setAnimationSpeed(DEFAULT, 6);
	sprite->addKeyframe(DEFAULT, glm::vec2(0.0f, 0.0f));

	sprite->changeAnimation(0);
}

//sprite->setPosition(glm::vec2(float(5.0f), float(3.0f)));

PowerUp::~PowerUp()
{
}

void PowerUp::update(int deltaTime) {
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(posPowerUp.x - map->getScroll()), float(posPowerUp.y)));
}

void PowerUp::setTileMap(TileMap *tileMap) {
	map = tileMap;
}

void PowerUp::setPosition(const glm::vec2 &pos) {
	posPowerUp = pos;
	sprite->setPosition(glm::vec2(float(posPowerUp.x - map->getScroll()), float(posPowerUp.y)));
}

glm::vec2 PowerUp::ret_pos() {
	return posPowerUp;
}

glm::vec2 PowerUp::ret_size() {
	return size;
}

void PowerUp::render()
{
	sprite->render();
}
