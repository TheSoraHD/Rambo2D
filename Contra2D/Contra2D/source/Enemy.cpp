#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"

#define TURRET 0
#define SOLDIER_KAMIKAZE 1
#define SOLDIER_GROUND 2

enum TurretAnims
{
	LEFT, L_TO_UP, UP_TO_L, UP, UP_TO_R, R_TO_UP, RIGHT, R_TO_D, D_TO_R, DOWN, D_TO_L, L_TO_D
};
enum GroundAnims
{
	GROUND
};

void Enemy::init(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram, Player *target, int typeOf)
{
	typeofEnemy = typeOf;
	switch (typeofEnemy) {
		case TURRET:
			spritesheet.loadFromFile("images/turrets.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
			turretAnim();
			break;
		case SOLDIER_GROUND:
			spritesheet.loadFromFile("images/soldier_ground.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(1.0f, 1.0f), &spritesheet, &shaderProgram);
			sprite->setNumberAnimations(1);

			sprite->setAnimationSpeed(GROUND, 5);
			sprite->addKeyframe(GROUND, glm::vec2(0.0f, 0.0f));
			break;
	}
	sprite->changeAnimation(0);
	//sprite->setPosition(glm::vec2(float(posEnemy.x - map->getScroll()), float(posEnemy.y)));
	player = target;
}

void Enemy::update(int deltaTime)
{
	turretAim();

	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(posEnemy.x - map->getScroll()), float(posEnemy.y)));
}

void Enemy::turretAim() {

	if (Game::instance().getKey('1')) sprite->changeAnimation(RIGHT);
	if (Game::instance().getKey('2')) sprite->changeAnimation(R_TO_D);
	if (Game::instance().getKey('3')) sprite->changeAnimation(DOWN);
	if (Game::instance().getKey('4')) sprite->changeAnimation(D_TO_L);
	if (Game::instance().getKey('5')) sprite->changeAnimation(LEFT);
	if (Game::instance().getKey('6')) sprite->changeAnimation(L_TO_UP);
	if (Game::instance().getKey('7')) sprite->changeAnimation(UP);
	if (Game::instance().getKey('8')) sprite->changeAnimation(UP_TO_R);

	/*const glm::vec2 posPlayer = player->sharePosition();
	if (posPlayer.x - posEnemy.x > 0) {
		if (posPlayer.y - posEnemy.y > 0) {
			sprite->changeAnimation(U_TO_R);
		}
	}*/
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

void Enemy::turretAnim() { 
	sprite->setNumberAnimations(12);

	sprite->setAnimationSpeed(RIGHT, 5);
	sprite->addKeyframe(RIGHT, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(R_TO_D, 5);
	sprite->addKeyframe(R_TO_D, glm::vec2(0.0f, 0.0f));
	sprite->addKeyframe(R_TO_D, glm::vec2(0.25f, 0.0f));
	sprite->addKeyframe(R_TO_D, glm::vec2(0.5f, 0.0f));
	sprite->addKeyframe(R_TO_D, glm::vec2(0.0f, 0.25f));

	sprite->setAnimationSpeed(D_TO_R, 5);
	sprite->addKeyframe(D_TO_R, glm::vec2(0.0f, 0.25f));
	sprite->addKeyframe(D_TO_R, glm::vec2(0.5f, 0.0f));
	sprite->addKeyframe(D_TO_R, glm::vec2(0.25f, 0.0f));
	sprite->addKeyframe(D_TO_R, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(DOWN, 5);
	sprite->addKeyframe(DOWN, glm::vec2(0.0f, 0.25f));

	sprite->setAnimationSpeed(D_TO_L, 5);
	sprite->addKeyframe(D_TO_L, glm::vec2(0.0f, 0.25f));
	sprite->addKeyframe(D_TO_L, glm::vec2(0.25f, 0.25f));
	sprite->addKeyframe(D_TO_L, glm::vec2(0.5f, 0.25f));
	sprite->addKeyframe(D_TO_L, glm::vec2(0.0f, 0.5f));

	sprite->setAnimationSpeed(L_TO_D, 5);
	sprite->addKeyframe(L_TO_D, glm::vec2(0.0f, 0.5f));
	sprite->addKeyframe(L_TO_D, glm::vec2(0.5f, 0.25f));
	sprite->addKeyframe(L_TO_D, glm::vec2(0.25f, 0.25f));
	sprite->addKeyframe(L_TO_D, glm::vec2(0.0f, 0.25f));

	sprite->setAnimationSpeed(LEFT, 5);
	sprite->addKeyframe(LEFT, glm::vec2(0.0f, 0.5f));

	sprite->setAnimationSpeed(L_TO_UP, 5);
	sprite->addKeyframe(L_TO_UP, glm::vec2(0.0f, 0.5f));
	sprite->addKeyframe(L_TO_UP, glm::vec2(0.25f, 0.5f));
	sprite->addKeyframe(L_TO_UP, glm::vec2(0.5f, 0.5f));
	sprite->addKeyframe(L_TO_UP, glm::vec2(0.0f, 0.75f));

	sprite->setAnimationSpeed(UP_TO_L, 5);
	sprite->addKeyframe(UP_TO_L, glm::vec2(0.0f, 0.75f));
	sprite->addKeyframe(UP_TO_L, glm::vec2(0.5f, 0.5f));
	sprite->addKeyframe(UP_TO_L, glm::vec2(0.25f, 0.5f));
	sprite->addKeyframe(UP_TO_L, glm::vec2(0.0f, 0.5f));

	sprite->setAnimationSpeed(UP, 5);
	sprite->addKeyframe(UP, glm::vec2(0.0f, 0.75f));

	sprite->setAnimationSpeed(UP_TO_R, 5);
	sprite->addKeyframe(UP_TO_R, glm::vec2(0.0f, 0.75f));
	sprite->addKeyframe(UP_TO_R, glm::vec2(0.25f, 0.75f));
	sprite->addKeyframe(UP_TO_R, glm::vec2(0.5f, 0.75f));
	sprite->addKeyframe(UP_TO_R, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(R_TO_UP, 5);
	sprite->addKeyframe(R_TO_UP, glm::vec2(0.0f, 0.0f));
	sprite->addKeyframe(R_TO_UP, glm::vec2(0.5f, 0.75f));
	sprite->addKeyframe(R_TO_UP, glm::vec2(0.25f, 0.75f));
	sprite->addKeyframe(R_TO_UP, glm::vec2(0.0f, 0.75f));
}