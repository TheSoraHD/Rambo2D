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
	SHOOT_RIGHT, SHOOT_LEFT,
	MOVE_UR, MOVE_DR, MOVE_UL, MOVE_DL,
	DEATH, UP_LEVEL2, DOWN_LEVEL2

};


void Player::init(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram, BulletManager *bulletManager)
{
	bJumping = false;
	lifes = 2;
	cooldown_shot = 0;
	spritesheet.loadFromFile("images/lance_new2x.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 128), glm::vec2(0.125f, 0.125f), &spritesheet, &shaderProgram);
	aux = &shaderProgram;
	sprite->setNumberAnimations(21);
	
		sprite->setAnimationSpeed(STAND_LEFT, 6);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.125f, 0.f));

		sprite->setAnimationSpeed(STAND_RIGHT, 6);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.125f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 5);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f, 0.125f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.125f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.125f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.375f, 0.125f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.125f));

		sprite->setAnimationSpeed(MOVE_RIGHT, 5);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0f, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125f, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.375f, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.125f));

		sprite->setAnimationSpeed(LOOK_UP, 6);
		sprite->addKeyframe(LOOK_UP, glm::vec2(0.25f, 0.0f));
		sprite->addKeyframe(LOOK_UP, glm::vec2(0.375f, 0.f));

		sprite->setAnimationSpeed(LOOK_DOWN, 6);
		sprite->addKeyframe(LOOK_DOWN, glm::vec2(0.5f, 0.0f));
		sprite->addKeyframe(LOOK_DOWN, glm::vec2(0.625f, 0.0f));
		

		sprite->setAnimationSpeed(JUMP_LEFT, 6);
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.625f, 0.25f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.75f, 0.25f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.865f, 0.25f));

		sprite->setAnimationSpeed(JUMP_RIGHT, 6);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.625f, 0.25f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.75f, 0.25f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.865f, 0.25f));

		sprite->setAnimationSpeed(SHOOT_RIGHT, 6);
		sprite->addKeyframe(SHOOT_RIGHT, glm::vec2(0.0f, 0.375f));
		sprite->addKeyframe(SHOOT_RIGHT, glm::vec2(0.125f, 0.375f));
		sprite->addKeyframe(SHOOT_RIGHT, glm::vec2(0.25f, 0.375f));

		sprite->setAnimationSpeed(SHOOT_LEFT, 6);
		sprite->addKeyframe(SHOOT_LEFT, glm::vec2(0.0f, 0.375f));
		sprite->addKeyframe(SHOOT_LEFT, glm::vec2(0.125f, 0.375f));
		sprite->addKeyframe(SHOOT_LEFT, glm::vec2(0.25f, 0.375f));

		sprite->setAnimationSpeed(MOVE_UR, 6);
		sprite->addKeyframe(MOVE_UR, glm::vec2(0.0f, 0.5f));
		sprite->addKeyframe(MOVE_UR, glm::vec2(0.125f, 0.5f));
		sprite->addKeyframe(MOVE_UR, glm::vec2(0.25f, 0.5f));

		sprite->setAnimationSpeed(MOVE_DR, 6);
		sprite->addKeyframe(MOVE_DR, glm::vec2(0.0f, 0.75f));
		sprite->addKeyframe(MOVE_DR, glm::vec2(0.125f, 0.75f));
		sprite->addKeyframe(MOVE_DR, glm::vec2(0.25f, 0.75f));

		sprite->setAnimationSpeed(MOVE_UL, 6);
		sprite->addKeyframe(MOVE_UL, glm::vec2(0.0f, 0.5f));
		sprite->addKeyframe(MOVE_UL, glm::vec2(0.125f, 0.5f));
		sprite->addKeyframe(MOVE_UL, glm::vec2(0.25f, 0.5f));

		sprite->setAnimationSpeed(MOVE_DL, 6);
		sprite->addKeyframe(MOVE_DL, glm::vec2(0.0f, 0.75f));
		sprite->addKeyframe(MOVE_DL, glm::vec2(0.125f, 0.75f));
		sprite->addKeyframe(MOVE_DL, glm::vec2(0.25f, 0.75f));

		sprite->setAnimationSpeed(DEATH, 6);
		sprite->addKeyframe(DEATH, glm::vec2(0.0f, 0.25f));
		sprite->addKeyframe(DEATH, glm::vec2(0.125f, 0.25f));
		sprite->addKeyframe(DEATH, glm::vec2(0.25f, 0.25f));

		sprite->setAnimationSpeed(UP_LEVEL2, 6);
		sprite->addKeyframe(UP_LEVEL2, glm::vec2(0.75f, 0.0f));
		sprite->addKeyframe(UP_LEVEL2, glm::vec2(0.875f, 0.0f));

		sprite->setAnimationSpeed(DOWN_LEVEL2, 6);
		sprite->addKeyframe(DOWN_LEVEL2, glm::vec2(0.75f, 0.125f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	bM = bulletManager;
}

void Player::update(int deltaTime)
{
	//if (Game::instance().getSpecialKey(GLUT_KEY_UP)) sound.playSFX("sfx/zawarudo.wav");
	sprite->update(deltaTime);

	movement();

	if ((Game::instance().getKey('z') || Game::instance().getKey('Z')) && cooldown_shot <= 0) { //disparar
		int direction = sprite->animation();
		if (direction == STAND_LEFT || direction == MOVE_LEFT || direction == JUMP_LEFT) { direction = 0; } //LEFT
		else if (direction == STAND_RIGHT || direction == MOVE_RIGHT || direction == JUMP_RIGHT) { direction = 1; } //RIGHT
		else if (direction == LOOK_UP) { direction = 2; } //UP
		else direction = 3; //DOWN

		bM->createPlayerBullet(posPlayer.x+10,posPlayer.y+60, direction, *aux);
		sound.playSFX("sfx/shoot.wav");
		cooldown_shot = 10;
	}
	--cooldown_shot;
	sprite->setPosition(glm::vec2(float(posPlayer.x - map->getScroll()), float(posPlayer.y)));
}

void Player::movement() {
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		posPlayer.x -= 2.5;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(64, 128)))
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
		posPlayer.x += 12.5;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(64, 128)))
		{
			posPlayer.x -= 2.5;
			sprite->changeAnimation(STAND_RIGHT);
		}
		else if (posPlayer.x >= (map->getScroll() + (SCREEN_WIDTH / 2))) //TO-DO: Stop scrolling at the end of the level + IS_PLATFORMER_LEVEL?
			map->increaseScroll(12.5);

		if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			if (sprite->animation() != MOVE_UR && !bJumping)
				sprite->changeAnimation(MOVE_UR);
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			if (sprite->animation() != MOVE_DR && !bJumping)
				sprite->changeAnimation(MOVE_DR);
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
	}
	else
	{
		if (sprite->animation() != STAND_LEFT && !bJumping)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == STAND_RIGHT && !bJumping)
			sprite->changeAnimation(STAND_RIGHT);
	}

	if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
			if (sprite->animation() != STAND_RIGHT) {
				sprite->changeAnimation(STAND_RIGHT);
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
				if (sprite->animation() != JUMP_RIGHT) {
					sprite->changeAnimation(JUMP_RIGHT);
				}
			}
		}
	}
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




