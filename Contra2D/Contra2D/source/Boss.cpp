#include "Boss.h"

enum BossAnims
{
	INTRO, PHASE1, PHASE2, PHASE3
};

enum MouthAnims
{
	OPEN, CLOSE
};

void Boss::init(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram, Player *target, BulletManager *bulletManager)
{
	spritesheet.loadFromFile("images/bossbase2x.png", TEXTURE_PIXEL_FORMAT_RGBA);
	bossBaseSprite = Sprite::createSprite(glm::ivec2(448, 256), glm::vec2(1.0f, 1.0f), &spritesheet, &shaderProgram);
	bossBaseSprite->setPosition(glm::vec2(1952.0f - map->getScroll(), 0.0f));
	bossHealth = 75;
	bM = bulletManager;
	cutsceneDelay = 120;
	isInvincible = true;
	isDefeated = false;
}

void Boss::defeated() {

}

void Boss::intro() {

}

void Boss::phase1() { //TWO ARMS LEFT

}

void Boss::phase2() { //ONE ARM LEFT

}

void Boss::phase3() { //ONLY MOUTH LEFT

}

void Boss::render() {
	bossBaseSprite->render();
}

void Boss::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Boss::update(int deltaTime) {
	bossBaseSprite->update(deltaTime);
	if (cutsceneDelay >= 0) {
		cutsceneDelay -= 0.1f * deltaTime;
	}
	else if (!isDefeated) {
		if (bossHealth <= 0) {
			defeated();
		}
		else {
			//AI
			if (bossHealth <= 25) phase3();
			else if (bossHealth <= 50) phase2();
			else phase1();
		}
	}
	bossBaseSprite->setPosition(glm::vec2(1952.0f - map->getScroll(), 0.0f));
}

bool Boss::isBossDefeated() {
	return (isDefeated && cutsceneDelay <= 0);
}