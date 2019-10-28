#include "Boss.h"

enum BossAnims
{
	INTRO, PHASE1, PHASE2, PHASE3, DEAD
};

enum MouthAnims
{
	OPEN, CLOSE
};

enum directions //1, 2, 3, 4
{
	LEFT, RIGHT, UP, DOWN, UR, DR, UL, DL
};

void Boss::init(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram, Player *target, BulletManager *bulletManager)
{
	spritesheet.loadFromFile("images/bossbase2x.png", TEXTURE_PIXEL_FORMAT_RGBA);
	bossBaseSprite = Sprite::createSprite(glm::ivec2(448, 256), glm::vec2(1.0f, 0.125f), &spritesheet, &shaderProgram);
	bossBaseSprite->setPosition(glm::vec2(1952.0f - map->getScroll(), 0.0f));
	bossBaseSprite->setNumberAnimations(5);

	bossBaseSprite->setAnimationSpeed(INTRO, 2);
	bossBaseSprite->addKeyframe(INTRO, glm::vec2(0.0f, 0.0f));
	bossBaseSprite->addKeyframe(INTRO, glm::vec2(0.0f, 0.125f));
	bossBaseSprite->addKeyframe(INTRO, glm::vec2(0.0f, 0.25f));
	bossBaseSprite->addKeyframe(INTRO, glm::vec2(0.0f, 0.375f));
	bossBaseSprite->addKeyframe(INTRO, glm::vec2(0.0f, 0.375f));
	bossBaseSprite->addKeyframe(INTRO, glm::vec2(0.0f, 0.375f));

	bossBaseSprite->setAnimationSpeed(PHASE1, 1);
	bossBaseSprite->addKeyframe(PHASE1, glm::vec2(0.0f, 0.5f));

	bossBaseSprite->setAnimationSpeed(PHASE2, 1);
	bossBaseSprite->addKeyframe(PHASE2, glm::vec2(0.0f, 0.625f));

	bossBaseSprite->setAnimationSpeed(PHASE3, 1);
	bossBaseSprite->addKeyframe(PHASE3, glm::vec2(0.0f, 0.75f));

	bossBaseSprite->setAnimationSpeed(DEAD, 1);
	bossBaseSprite->addKeyframe(DEAD, glm::vec2(0.0f, 0.875f));

	bossBaseSprite->changeAnimation(0);

	bossHealth = 75;
	bM = bulletManager;
	sP = shaderProgram;
	cutsceneDelay = 300;
	isInvincible = true;
	isDefeated = false;

	sM.playSFX("sfx/godzilla.wav");
}

void Boss::defeated() {
	cutsceneDelay = 300;
	sM.stopBGM();
	sM.playSFX("sfx/booom.wav");
	isDefeated = true;
}

void Boss::phase1() { //75HP
	bossBaseSprite->changeAnimation(1);
	bM->createPlayerBullet(1952.0f, 100.0f, DOWN, true, sP);
}

void Boss::phase2() { //50HP
	bossBaseSprite->changeAnimation(2);
}

void Boss::phase3() { //25HP
	bossBaseSprite->changeAnimation(3);
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
		bossHealth--;
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

bool Boss::stopMusic() {
	return (isDefeated && cutsceneDelay > 0);
}

bool Boss::isBossDefeated() {
	return (isDefeated && cutsceneDelay <= 0);
}