#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>
#include "HUD.h"

void HUD::init(ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/medals2x.png", TEXTURE_PIXEL_FORMAT_RGBA);
	medal1 = Sprite::createSprite(glm::ivec2(30, 48), glm::vec2(0.5f, 1.0f), &spritesheet, &shaderProgram);
	medal2 = Sprite::createSprite(glm::ivec2(30, 48), glm::vec2(0.5f, 1.0f), &spritesheet, &shaderProgram);
	spritesheet2.loadFromFile("images/stopwatch.png", TEXTURE_PIXEL_FORMAT_RGBA);
	clock = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(1.0f, 1.0f), &spritesheet2, &shaderProgram);
}

void HUD::render()
{
	medal1->render();
	medal2->render();
	clock->render();
}

void HUD::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void HUD::setPosition(int lifes, bool zawarudo)
{
	if (lifes > 1) {
		medal1->setPosition(glm::vec2(38.0f, 20.0f));
		if (lifes > 2) {
			medal2->setPosition(glm::vec2(80.0f, 20.0f));
		}
		else medal2->setPosition(glm::vec2(10000.0f, 0.0f));
	}
	else {
		medal1->setPosition(glm::vec2(10000.0f, 0.0f));
		medal2->setPosition(glm::vec2(10000.0f, 0.0f));
	}
	if (!zawarudo)
		clock->setPosition(glm::vec2(25.0f, 425.0f));
	else
		clock->setPosition(glm::vec2(10000.0f, 425.0f));
	
}

void HUD::update(int deltaTime, int lifes, bool zawarudo) {
	setPosition(lifes, zawarudo);
	medal1->update(deltaTime);
	medal2->update(deltaTime);
	clock->update(deltaTime);
}