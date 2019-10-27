#include "Bridge.h"



void Bridge::init(int length, const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/bridge2x.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = new Sprite[length];
	sprite[0].Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.0f, 0.0f), &spritesheet, &shaderProgram);
	sprite[0].setPosition(glm::vec2(float(posBridge.x), float(posBridge.y)));
	for (int i = 0; i < length - 2; i++) {
		sprite[i + 1].Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.25f, 0.0f), &spritesheet, &shaderProgram);
		sprite[i + 1].setPosition(glm::vec2(float(posBridge.x + (i * 64)), float(posBridge.y)));
	}
	sprite[length - 1].Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5f, 0.0f), &spritesheet, &shaderProgram);
	sprite[length - 1].setPosition(glm::vec2(float(posBridge.x + (length * 64)), float(posBridge.y)));
	m_length = length;
}

void Bridge::render()
{
	for (int i = 0; i < m_length; i++) {
		sprite[i].render();
	}
}

void Bridge::setPosition(const glm::vec2 &pos)
{
	posBridge = pos;
	for (int i = 0; i < m_length; i++) {
		sprite[i].setPosition(glm::vec2(float(posBridge.x + (i * 64) - map->getScroll()), float(posBridge.y)));
	}
}

void Bridge::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Bridge::update(int deltaTime)
{
	for (int i = 0; i < m_length; i++) {
		sprite[i].update(deltaTime);
		sprite[i].setPosition(glm::vec2(float(posBridge.x + (i * 64) - map->getScroll()), float(posBridge.y)));
	}
}