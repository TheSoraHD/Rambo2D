#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Explosion.h"

enum ExplosionAnims
{
	DEFAULT
};

Explosion::Explosion()
{
	posExplosion.x = NULL;
	posExplosion.y = NULL; 
}


Explosion::~Explosion()
{
}

void Explosion::init(glm::vec2 pos_explosion, ShaderProgram &shaderProgram) {
	posExplosion = pos_explosion;
	timer = 50;

	spritesheet.loadFromFile("images/explosion2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(128, 128), glm::vec2(0.0625f, 1.0f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(DEFAULT, 5);
	sprite->addKeyframe(DEFAULT, glm::vec2(0.0f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.0625f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.125f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.1875f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.25f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.3125f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.375f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.4375f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.5f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.5625f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.625f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.6875f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.75f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.8125f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.875f, 0.0f));

	sprite->changeAnimation(0);

	//this->setPosition();

}

void Explosion::render()
{
	sprite->render();
}

void Explosion::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Explosion::setPosition()
{
	sprite->setPosition(glm::vec2(float(posExplosion.x - map->getScroll()), float(posExplosion.y)));
}

void Explosion::update() {
	--timer;
}

int Explosion::ret_timer() {
	return timer;
}