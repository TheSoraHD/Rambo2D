#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 120
#define FALL_STEP 4

ShaderProgram *aux;

enum PlayerAnims
{
	STAND_RIGHT, STAND_LEFT,
	MOVE_LEFT, MOVE_RIGHT,
	LOOK_UP, LOOK_DOWN,
	JUMP_LEFT, JUMP_RIGHT,
	SHOOT_RIGHT, SHOOT_LEFT, SHOOT_DOWN,
	MOVE_UR, MOVE_DR, MOVE_UL, MOVE_DL,
	UP_LEVEL2, DOWN_LEVEL2,
	DEATH, DEAD

};

enum directions
{
	LEFT, RIGHT, UP, DOWN, UR, DR, UL, DL
};

void Player::init(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram, BulletManager *bulletManager)
{
	god_mode = false;
	bJumping = false;
	spreadGun = false;
	left = false;
	hurt = false;
	lifes = 2;
	cooldown_shot = 0;
	cooldown_dead = 0;
	//posPlayer.x = 1;
	//posPlayer.y = 3;
	spritesheet.loadFromFile("images/lance2x.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 128), glm::vec2(0.0625f, 0.125f), &spritesheet, &shaderProgram);
	aux = &shaderProgram;
	size.x = 64;
	size.y = 64;
	sprite->setNumberAnimations(23);
	
		sprite->setAnimationSpeed(STAND_LEFT, 6);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.5f, 0.f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.5625f, 0.f));

		sprite->setAnimationSpeed(STAND_RIGHT, 6);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0f, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0625f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 5);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.125f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5625f, 0.125f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.625f, 0.125f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.6875f, 0.125f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.75f, 0.125f));

		sprite->setAnimationSpeed(MOVE_RIGHT, 5);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0f, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0625f, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125f, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.1875f, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.125f));

		sprite->setAnimationSpeed(LOOK_UP, 6);
		sprite->addKeyframe(LOOK_UP, glm::vec2(0.125f, 0.0f));
		sprite->addKeyframe(LOOK_UP, glm::vec2(0.1875f, 0.0f));

		sprite->setAnimationSpeed(LOOK_DOWN, 6);
		sprite->addKeyframe(LOOK_DOWN, glm::vec2(0.25f, 0.0f));
		sprite->addKeyframe(LOOK_DOWN, glm::vec2(0.3125f, 0.0f));

		sprite->setAnimationSpeed(JUMP_LEFT, 6);
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.25f, 0.25f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.3125f, 0.25f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.375f, 0.25f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.4325f, 0.25f));

		sprite->setAnimationSpeed(JUMP_RIGHT, 6);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.25f, 0.25f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.3125f, 0.25f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.375f, 0.25f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.4325f, 0.25f));

		sprite->setAnimationSpeed(SHOOT_RIGHT, 6);
		sprite->addKeyframe(SHOOT_RIGHT, glm::vec2(0.0f, 0.375f));
		sprite->addKeyframe(SHOOT_RIGHT, glm::vec2(0.0625f, 0.375f));
		sprite->addKeyframe(SHOOT_RIGHT, glm::vec2(0.125f, 0.375f));

		sprite->setAnimationSpeed(SHOOT_LEFT, 6);
		sprite->addKeyframe(SHOOT_LEFT, glm::vec2(0.5f, 0.375f));
		sprite->addKeyframe(SHOOT_LEFT, glm::vec2(0.5625f, 0.375f));
		sprite->addKeyframe(SHOOT_LEFT, glm::vec2(0.625f, 0.375f));

		sprite->setAnimationSpeed(SHOOT_DOWN, 6);
		sprite->addKeyframe(SHOOT_DOWN, glm::vec2(0.25f, 0.25f));
		sprite->addKeyframe(SHOOT_DOWN, glm::vec2(0.3125f, 0.25f));
		sprite->addKeyframe(SHOOT_DOWN, glm::vec2(0.375f, 0.25f));
		sprite->addKeyframe(SHOOT_DOWN, glm::vec2(0.4325f, 0.25f));

		sprite->setAnimationSpeed(MOVE_UR, 6);
		sprite->addKeyframe(MOVE_UR, glm::vec2(0.0f, 0.5f));
		sprite->addKeyframe(MOVE_UR, glm::vec2(0.0625f, 0.5f));
		sprite->addKeyframe(MOVE_UR, glm::vec2(0.125f, 0.5f));

		sprite->setAnimationSpeed(MOVE_DR, 6);
		sprite->addKeyframe(MOVE_DR, glm::vec2(0.0f, 0.75f));
		sprite->addKeyframe(MOVE_DR, glm::vec2(0.0625f, 0.75f));
		sprite->addKeyframe(MOVE_DR, glm::vec2(0.125f, 0.75f));

		sprite->setAnimationSpeed(MOVE_UL, 6);
		sprite->addKeyframe(MOVE_UL, glm::vec2(0.50f, 0.5f));
		sprite->addKeyframe(MOVE_UL, glm::vec2(0.5625f, 0.5f));
		sprite->addKeyframe(MOVE_UL, glm::vec2(0.625f, 0.5f));

		sprite->setAnimationSpeed(MOVE_DL, 6);
		sprite->addKeyframe(MOVE_DL, glm::vec2(0.5f, 0.75f));
		sprite->addKeyframe(MOVE_DL, glm::vec2(0.5625f, 0.75f));
		sprite->addKeyframe(MOVE_DL, glm::vec2(0.625f, 0.75f));

		sprite->setAnimationSpeed(UP_LEVEL2, 6);
		sprite->addKeyframe(UP_LEVEL2, glm::vec2(0.375f, 0.0f));
		sprite->addKeyframe(UP_LEVEL2, glm::vec2(0.4375f, 0.0f));

		sprite->setAnimationSpeed(DOWN_LEVEL2, 6);
		sprite->addKeyframe(DOWN_LEVEL2, glm::vec2(0.375f, 0.125f));

		sprite->setAnimationSpeed(DEATH, 2);
		sprite->addKeyframe(DEATH, glm::vec2(0.0f, 0.25f));
		sprite->addKeyframe(DEATH, glm::vec2(0.0625f, 0.25f));
		sprite->addKeyframe(DEATH, glm::vec2(0.125f, 0.25f));

		sprite->setAnimationSpeed(DEAD, 6);
		sprite->addKeyframe(DEAD, glm::vec2(0.125f, 0.25f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	bM = bulletManager;
}

void Player::update(int deltaTime)
{
	//if (Game::instance().getSpecialKey(GLUT_KEY_UP)) sound.playSFX("sfx/zawarudo.wav");
	sprite->update(deltaTime);
	if (cooldown_dead > 450) {
		--cooldown_dead;
		if (cooldown_dead == 560) {
			if (sprite->animation() != DEAD) sprite->changeAnimation(DEAD);
		}
		if (cooldown_dead == 450) {
			//respawn with inmunity
			posPlayer.x = map->getScroll()+10;
			posPlayer.y = 5;
			sprite->setPosition(glm::vec2(float(posPlayer.x - map->getScroll()), float(posPlayer.y)));
			//if (sprite->animation() != JUMP_RIGHT) sprite->changeAnimation(JUMP_RIGHT); //no cambia animación because reasons
		}
	}
	else {
		if (cooldown_dead > 0) {
			--cooldown_dead;
			if (cooldown_dead == 0) hurt = false; //inmunity off
		}

		movement();
		int offset_x = 0;
		int offset_y = 0;
		if ((Game::instance().getKey('2'))) god_mode = true;
		if ((Game::instance().getKey('3'))) god_mode = false;
		if ((Game::instance().getKey('z') || Game::instance().getKey('Z')) && cooldown_shot <= 0) { //disparar
			int direction = RIGHT;
			switch (sprite->animation()) {
			case (STAND_RIGHT):
				direction = RIGHT; offset_x = 36; offset_y = 78;
				break;
			case (STAND_LEFT):
				direction = LEFT; offset_x = 0; offset_y = 78;
				break;
			case (MOVE_LEFT):
				direction = LEFT; offset_x = 0; offset_y = 78;
				break;
			case (LOOK_UP):
				direction = UP; offset_x = 20; offset_y = 40;
				break;
			case (LOOK_DOWN):
				direction = RIGHT; offset_x = 60; offset_y = 105;
				break;
			case (JUMP_LEFT):
				direction = LEFT; offset_x = 0; offset_y = 78;
				break;
			case (JUMP_RIGHT):
				direction = RIGHT; offset_x = 36; offset_y = 78;
				break;
			case (SHOOT_RIGHT):
				direction = RIGHT; offset_x = 36; offset_y = 78;
				break;
			case (SHOOT_LEFT):
				direction = LEFT; offset_x = 0; offset_y = 78;
				break;
			case (SHOOT_DOWN):
				direction = DOWN; offset_x = 16; offset_y = 78;
				break;
			case (MOVE_UR):
				direction = UR; offset_x = 31; offset_y = 58;
				break;
			case (MOVE_DR):
				direction = DR; offset_x = 33; offset_y = 90;
				break;
			case (MOVE_UL):
				direction = UL; offset_x = 0; offset_y = 58;
				break;
			case (MOVE_DL):
				direction = DL; offset_x = 0; offset_y = 90;
				break;
			case (UP_LEVEL2):
				direction = UP; offset_x = 20; offset_y = 40;
				break;
			case (DOWN_LEVEL2):
				direction = UP; offset_x = 20; offset_y = 40;
				break;
			}
			bM->createPlayerBullet(posPlayer.x + (int)offset_x, posPlayer.y + (int)offset_y, direction, spreadGun, *aux);
			sound.playSFX("sfx/shoot.wav");
			cooldown_shot = 10;
		}
		--cooldown_shot;
	}
	sprite->setPosition(glm::vec2(float(posPlayer.x - map->getScroll()), float(posPlayer.y)));
}

void Player::movement() {
	
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		left = true;
		posPlayer.x -= 2.5;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 128)) || posPlayer.x <= map->getScroll())
		{
			posPlayer.x += 2.5;
			sprite->changeAnimation(STAND_LEFT);
		}
		if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			if (sprite->animation() != MOVE_UL && !bJumping)
				sprite->changeAnimation(MOVE_UL);
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			if (sprite->animation() != MOVE_DL && !bJumping)
				sprite->changeAnimation(MOVE_DL);
			else if (sprite->animation() != SHOOT_DOWN && bJumping)
				sprite->changeAnimation(SHOOT_DOWN);
		}
		else if (Game::instance().getKey('z') || Game::instance().getKey('Z')) {
			if (sprite->animation() != SHOOT_LEFT && !bJumping)
				sprite->changeAnimation(SHOOT_LEFT);
		}
		else if (sprite->animation() != MOVE_LEFT && !bJumping)
			sprite->changeAnimation(MOVE_LEFT);
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		left = false;
		posPlayer.x += 12.5;

		if(map->collisionMoveRight(posPlayer, glm::ivec2(64, 128)) || posPlayer.x >= (map->getLevelWidth() - 64.0f))
		{
			posPlayer.x -= 12.5;
			sprite->changeAnimation(STAND_RIGHT);
		}
		else if (posPlayer.x >= (map->getScroll() + (SCREEN_WIDTH / 2)) && posPlayer.x < (map->getLevelWidth() - (SCREEN_WIDTH / 2) - 32.0f)) //Level 3 Hack
			map->increaseScroll(12.5);

		if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			if (sprite->animation() != MOVE_UR && !bJumping)
				sprite->changeAnimation(MOVE_UR);
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			if (sprite->animation() != MOVE_DR && !bJumping)
				sprite->changeAnimation(MOVE_DR);
			else if (sprite->animation() != SHOOT_DOWN && bJumping)
				sprite->changeAnimation(SHOOT_DOWN);
		}
		else if (Game::instance().getKey('z') || Game::instance().getKey('Z')) {
			if (sprite->animation() != SHOOT_RIGHT && !bJumping)
				sprite->changeAnimation(SHOOT_RIGHT);
		}
		else if (sprite->animation() != MOVE_RIGHT && !bJumping)
			sprite->changeAnimation(MOVE_RIGHT);

	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		if (sprite->animation() != LOOK_UP && !bJumping) {
			sprite->changeAnimation(LOOK_UP);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		if (sprite->animation() != LOOK_DOWN && !bJumping) {
			sprite->changeAnimation(LOOK_DOWN);
		}
		else if (sprite->animation() != SHOOT_DOWN && bJumping) {
			sprite->changeAnimation(SHOOT_DOWN);
		}
	}
	else
	{
		if (sprite->animation() != STAND_LEFT && left &&!bJumping)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() != STAND_RIGHT && !left && !bJumping)
			sprite->changeAnimation(STAND_RIGHT);
	}

	if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
			if (sprite->animation() != STAND_RIGHT && !left) {
				sprite->changeAnimation(STAND_RIGHT);
			}
			else if (sprite->animation() != STAND_LEFT && left) {
				sprite->changeAnimation(STAND_LEFT);
			}
			sound.playSFX("sfx/hit_ground.wav");
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(64, 128), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(64, 128), &posPlayer.y))
		{
			if (Game::instance().getKey('x') || Game::instance().getKey('X')) //saltar
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
				sound.playSFX("sfx/jump.wav");
				if (sprite->animation() != JUMP_RIGHT && !left) {
					sprite->changeAnimation(JUMP_RIGHT);
				}
				else if (sprite->animation() != JUMP_LEFT && left) {
					sprite->changeAnimation(JUMP_LEFT);
				}
			}
		}
	}
}

glm::vec2 Player::ret_pos() {
	return posPlayer;
}

glm::vec2 Player::ret_size() {
	return size;
}

void Player::activateSpread(bool powerUp) {
	spreadGun = powerUp;
}

void Player::hit() {
	if (!hurt && !god_mode) {
		hurt = true;
		--lifes;
		if (sprite->animation() != DEATH)
			sprite->changeAnimation(DEATH);
		cooldown_dead = 600;
		sound.playSFX("sfx/playerhit.wav");
	}
}

bool Player::ret_hurt() {
	return hurt;
}

bool Player::isgod() {
	return god_mode;
}

bool Player::game_over() {
	return ((lifes == 0) && (cooldown_dead == 451));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(posPlayer.x - map->getScroll()), float(posPlayer.y)));
}

const glm::vec2 Player::sharePosition() {
	return glm::vec2(float(posPlayer.x), float(posPlayer.y));
}
