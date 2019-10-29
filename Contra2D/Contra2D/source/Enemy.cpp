#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"

#define TURRET 0
#define SOLDIER 1
#define SOLDIER_2ND_LEVEL 2

enum directions_bullets
{
	LEFT_BULL, RIGHT_BULL, UP_BULL, DOWN_BULL, UR_BULL, DR_BULL, UL_BULL, DL_BULL
};

enum TurretAnims
{
	LEFT, L_TO_UP, UP_TO_L, UP, UP_TO_R, R_TO_UP, RIGHT, R_TO_D, D_TO_R, DOWN, D_TO_L, L_TO_D
};
enum SoldierAnims
{
	DEFAULT
};

void Enemy::init(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram, Player *target, int typeOf, BulletManager *bulletManager)
{
	typeofEnemy = typeOf;
	cooldown = 50;
	aux = &shaderProgram;
	switch (typeofEnemy) {
		case TURRET:
			spritesheet.loadFromFile("images/turrets.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
			size.x = 64;
			size.y = 64;
			health = 10;
			turretAnim();
			break;
		case SOLDIER:
			spritesheet.loadFromFile("images/soldier2x.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5f, 1.0f), &spritesheet, &shaderProgram);
			sprite->setNumberAnimations(1);
			size.x = 34;
			size.y = 64;
			health = 5;
			sprite->setAnimationSpeed(DEFAULT, 5);
			sprite->addKeyframe(DEFAULT, glm::vec2(0.0f, 0.0f));
			sprite->addKeyframe(DEFAULT, glm::vec2(0.5f, 0.0f));
			break;
		case SOLDIER_2ND_LEVEL:
			spritesheet.loadFromFile("images/soldierLevel2_2x.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite = Sprite::createSprite(glm::ivec2(32, 64), glm::vec2(1.0f, 1.0f), &spritesheet, &shaderProgram);
			sprite->setNumberAnimations(1);
			size.x = 23;
			size.y = 64;
			health = 7;
			sprite->setAnimationSpeed(DEFAULT, 5);
			sprite->addKeyframe(DEFAULT, glm::vec2(0.0f, 0.0f));
			break;
		/*case SOLDIER_KAMIKAZE:
			spritesheet.loadFromFile("images/kamikaze2x.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite = Sprite::createSprite(glm::ivec2(32, 64), glm::vec2(0.125f, 1.0f), &spritesheet, &shaderProgram);
			sprite->setNumberAnimations(1);
			size.x = 32;
			size.y = 64;
			health = 1;
			sprite->setAnimationSpeed(RUN, 6);
			//sprite->addKeyframe(RUN, glm::vec2(0.75f, 0.0f));
			sprite->addKeyframe(RUN, glm::vec2(0.625f, 0.0f));
			sprite->addKeyframe(RUN, glm::vec2(0.5f, 0.0f));
			sprite->addKeyframe(RUN, glm::vec2(0.375f, 0.0f));
			sprite->addKeyframe(RUN, glm::vec2(0.25f, 0.0f));
			sprite->addKeyframe(RUN, glm::vec2(0.125f, 0.0f));
			sprite->addKeyframe(RUN, glm::vec2(0.0f, 0.0f));
			
			break;*/
	}
	sprite->changeAnimation(0);
	//sprite->setPosition(glm::vec2(float(posEnemy.x - map->getScroll()), float(posEnemy.y)));
	player = target;
	bM = bulletManager;
}

void Enemy::update(int deltaTime)
{
	if (typeofEnemy == TURRET) turretAim();
	else soldierShoot();
	if (sprite != NULL) {
		sprite->update(deltaTime);
		sprite->setPosition(glm::vec2(float(posEnemy.x - map->getScroll()), float(posEnemy.y)));
	}
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


void Enemy::soldierShoot() {
	if (cooldown <= 0) {
		switch (typeofEnemy) {
			case SOLDIER:
				bM->createEnemyBullet(posEnemy.x, posEnemy.y + 5, LEFT_BULL, false, *aux, 1.0f);
				cooldown = 100;
				break;
			case SOLDIER_2ND_LEVEL:
				bM->createEnemyBullet(posEnemy.x + 11, posEnemy.y + 35, DOWN_BULL, true, *aux, 1.0f);
				cooldown = 150;
				break;

		}
	}
	else --cooldown;
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

glm::vec2 Enemy::ret_pos() {
	if (this != NULL) {
		glm::vec2 posaux = posEnemy;
		if (typeofEnemy == SOLDIER) {
			posaux.x += 20;
		}
		return posaux;
	}
	return glm::vec2(0.0f,0.0f);
}

glm::vec2 Enemy::ret_size() {
	if (this != NULL)
		return size;
	return glm::vec2(0.0f, 0.0f);
}

void Enemy::hit() {
	if (this != NULL) {
		sound.playSFX("sfx/Soldier_death.wav");
		--health;
		if (health == 0) {
			sprite = NULL;
		}
	}
}
	

int Enemy::health_remaining() {
	if (this != NULL)
		return health;
	return 0;
}