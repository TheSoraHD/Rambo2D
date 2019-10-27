#include "Bridge.h"



void Bridge::init(int length, const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/bridge2x.png", TEXTURE_PIXEL_FORMAT_RGBA);
	//for (int i = 0; i < sprite->size(); ++i)
	//	sprite->push_back();
	sprite = new vector<Sprite>(length);
	sprite->at(0).createSprite(glm::ivec2(64, 64), glm::vec2(0.0f, 0.0f), &spritesheet, &shaderProgram);
	sprite->at(0).setPosition(glm::vec2(tileMapPos.x - map->getScroll(), tileMapPos.y));
	for (int i = 0; i < length - 2; i++) {
		sprite->at(i + 1).createSprite(glm::ivec2(64, 64), glm::vec2(0.25f, 0.0f), &spritesheet, &shaderProgram);
		sprite->at(i + 1).setPosition(glm::vec2(tileMapPos.x + 64*(i+1) + map->getScroll(), tileMapPos.y));
	}
	sprite->at(length - 1).createSprite(glm::ivec2(64, 64), glm::vec2(0.5f, 0.0f), &spritesheet, &shaderProgram);
	sprite->at(length - 1).setPosition(glm::vec2(tileMapPos.x + 64 * (length - 1) - map->getScroll(), tileMapPos.y));
}

void Bridge::render()
{
	for (int i = 0; i < sprite->size(); i++) {
		sprite->at(i).render();
	}
}

void Bridge::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Bridge::update(int deltaTime)
{

}