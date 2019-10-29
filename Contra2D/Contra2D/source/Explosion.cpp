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

	spritesheet.loadFromFile("images/explosion.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5f, 1.0f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(DEFAULT, 5);
	sprite->addKeyframe(DEFAULT, glm::vec2(0.0f, 0.0f));
	sprite->addKeyframe(DEFAULT, glm::vec2(0.5f, 0.0f));
	sprite->changeAnimation(0);

}

void Explosion::render()
{
	sprite->render();
}

void Explosion::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Explosion::setPosition(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	sprite->setPosition(glm::vec2(float(posExplosion.x - map->getScroll()), float(posExplosion.y)));
}