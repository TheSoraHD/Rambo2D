#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"


enum TurretAnims
{
	RIGHT, R_TO_D, DOWN, D_TO_L, LEFT, L_TO_UP, UP, U_TO_R
};

void Enemy::init(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/turrets.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(RIGHT, 3);
	sprite->addKeyframe(RIGHT, glm::vec2(0.0f, 0.5f));

	//sprite->setAnimationSpeed(R_TO_D, 3);
	//sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
	//sprite->addKeyframe(STAND_LEFT, glm::vec2(0.125f, 0.f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posEnemy.x), float(posEnemy.y)));

}

void Enemy::update(int deltaTime)
{
	sprite->update(deltaTime);

	sprite->setPosition(glm::vec2(float(posEnemy.x - map->getScroll()), float(posEnemy.y)));
}

void Enemy::render()
{
	sprite->render();
}

void Enemy::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2 &pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(posEnemy.x - map->getScroll()), float(posEnemy.y)));
}
