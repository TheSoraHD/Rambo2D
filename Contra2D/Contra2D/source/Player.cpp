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
	STAND_RIGHT, STAND_LEFT, MOVE_LEFT, MOVE_RIGHT, LOOK_UP, LOOK_DOWN, JUMP_LEFT, JUMP_RIGHT
};


void Player::init(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	lifes = 2;
	cooldown_shot = 0;
	spritesheet.loadFromFile("images/lance2x.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 128), glm::vec2(0.125f, 0.25f), &spritesheet, &shaderProgram);
	aux = &shaderProgram;
	sprite->setNumberAnimations(4);
	
		sprite->setAnimationSpeed(STAND_LEFT, 6);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.125f, 0.f));

		sprite->setAnimationSpeed(STAND_RIGHT, 6);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.125f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 5);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.375f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.25f));

		sprite->setAnimationSpeed(MOVE_RIGHT, 5);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0f, 0.25f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125f, 0.25f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.25f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.375f, 0.25f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.25f));
		
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	//if (Game::instance().getSpecialKey(GLUT_KEY_UP)) sound.playSFX("sfx/zawarudo.wav");
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2.5;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(64, 128)))
		{
			posPlayer.x += 2.5;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 12.5;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(64, 128)))
		{
			posPlayer.x -= 2.5;
			sprite->changeAnimation(STAND_RIGHT);
		}
		else if (posPlayer.x >= (map->getScroll() + (SCREEN_WIDTH / 2))) //TO-DO: Stop scrolling at the end of the level + IS_PLATFORMER_LEVEL?
			map->increaseScroll(12.5);
	}
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
			sound.playSFX("sfx/hit_ground.wav");
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(64, 128), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(64, 128), &posPlayer.y))
		{
			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
				sound.playSFX("sfx/jump.wav");
			}
		}
	}

	if ((Game::instance().getKey('z') || Game::instance().getKey('Z')) && cooldown_shot <= 0) { //disparar
		int direction = sprite->animation();
		if (direction == STAND_LEFT || direction == MOVE_LEFT || direction == JUMP_LEFT) { direction = 0; } //LEFT
		else if (direction == STAND_RIGHT || direction == MOVE_RIGHT || direction == JUMP_RIGHT) { direction = 1; } //RIGHT
		else if (direction == LOOK_UP) { direction = 2; } //UP
		else direction = 3; //DOWN

		BulletManager::instance().createPlayerBullet(posPlayer.x - map->getScroll(), posPlayer.y, direction, *aux);
		sound.playSFX("sfx/shoot.wav");
		cooldown_shot = 20;
	}
	--cooldown_shot;
	sprite->setPosition(glm::vec2(float(posPlayer.x - map->getScroll()), float(posPlayer.y)));
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




