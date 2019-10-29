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
	bossBaseSprite = Sprite::createSprite(glm::ivec2(448, 256), glm::vec2(1.0f, 0.1249f), &spritesheet, &shaderProgram);
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

	bossHealth = bossMaxHealth = 210;
	posEnemy.x = 2152.0f; posEnemy.y = 64.0f;
	size.x = 64.0f; size.y = 100.0f;
	bM = bulletManager;
	sP = shaderProgram;
	cutsceneDelay = 300;
	isInvincible = true;
	isDefeated = false;
	isPhase1 = isPhase2 = isPhase3 = false;
	phase3offset = 0.0f;
	phase3direction = 0;

	sM.playSFX("sfx/godzilla.wav");
}

void Boss::defeated() {
	bossBaseSprite->changeAnimation(4);
	cutsceneDelay = 300;
	sM.stopBGM();
	sM.playSFX("sfx/BigExplosion.wav");
	isInvincible = true;
	isDefeated = true;
}

void Boss::phase1() { //FULL HP
	if (!isPhase1) {
		bossBaseSprite->changeAnimation(1);
		cooldownMax = 200;
		isPhase1 = true;
		isInvincible = false;
	}
	if (cooldown > 100.0f && cooldown <= 102.0f) {
		bM->createEnemyBullet(1850.0f, 325.0f + (rand() % 3) * 10.0f, RIGHT, false, sP, 0.75);
	}
	if (cooldown <= 0) {
		cooldown = cooldownMax;
		bM->createEnemyBullet(2500.0f, 325.0f + (rand() % 3) * 10.0f, LEFT, false, sP, 0.75);
	}
}

void Boss::phase2() { //2/3 HP
	if (!isPhase2) {
		bossBaseSprite->changeAnimation(2);
		cooldownMax = 100;
		isPhase2 = true;
	}
	if (cooldown > 70.0f && cooldown <= 72.0f) {
		bM->createEnemyBullet(1850.0f + (rand() % 50), 50.0f + (rand() % 200), DR, false, sP, 0.85);
	}
	if (cooldown <= 0) {
		cooldown = cooldownMax;
		bM->createEnemyBullet(2500.0f - (rand() % 50), 50.0f + (rand() % 200), DL, false, sP, 0.85);
	}
}

void Boss::phase3(int deltaTime) { //1/3 HP
	bossBaseSprite->changeAnimation(3);
	cooldownMax = 12;
	if (cooldown <= 0) {
		cooldown = cooldownMax;
		bM->createEnemyBullet(1850.0f + phase3offset, 0.0f, DOWN, false, sP, 0.9);
		bM->createEnemyBullet(1900.0f + phase3offset, 0.0f, DOWN, false, sP, 0.9);
		bM->createEnemyBullet(1950.0f + phase3offset, 0.0f, DOWN, false, sP, 0.9);
		bM->createEnemyBullet(2000.0f + phase3offset, 0.0f, DOWN, false, sP, 0.9);
		bM->createEnemyBullet(2050.0f + phase3offset, 0.0f, DOWN, false, sP, 0.9);
		bM->createEnemyBullet(2100.0f + phase3offset, 0.0f, DOWN, false, sP, 0.9);

		bM->createEnemyBullet(2250.0f + phase3offset, 0.0f, DOWN, false, sP, 0.9);
		bM->createEnemyBullet(2300.0f + phase3offset, 0.0f, DOWN, false, sP, 0.9);
		bM->createEnemyBullet(2350.0f + phase3offset, 0.0f, DOWN, false, sP, 0.9);
		bM->createEnemyBullet(2400.0f + phase3offset, 0.0f, DOWN, false, sP, 0.9);
		bM->createEnemyBullet(2450.0f + phase3offset, 0.0f, DOWN, false, sP, 0.9);
		bM->createEnemyBullet(2500.0f + phase3offset, 0.0f, DOWN, false, sP, 0.9);
	}
	phase3direction += 0.1f * deltaTime;
	if (phase3direction % 800 < 100 || (phase3direction % 800 >= 600 && phase3direction % 800 < 700)){
		phase3offset += 0.15f * deltaTime;
	}
	else if ((phase3direction % 800 >= 200 && phase3direction % 800 < 300) || (phase3direction % 800 >= 400 && phase3direction % 800 < 500)) {
		phase3offset -= 0.15f * deltaTime;
	}
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
			cooldown -= 0.1f * deltaTime;
			if (bossHealth <= bossMaxHealth / 3) phase3(deltaTime);
			else if (bossHealth <= bossMaxHealth * 3 / 4) phase2();
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

glm::vec2 Boss::ret_pos() {
	return posEnemy;
}

glm::vec2 Boss::ret_size() {
	return size;
}

void Boss::hit() {
	if (!isInvincible) {
		bossHealth--;
		sM.playSFX("sfx/hit_ground.wav");
	}
}