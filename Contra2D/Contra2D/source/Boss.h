#ifndef _BOSS_INCLUDE
#define _BOSS_INCLUDE

#include "BulletManager.h"
#include "Enemy.h"
#include "Player.h"
#include "SoundManager.h"
#include "Sprite.h"
#include "TileMap.h"

class Boss
{
public:
	void init(const glm::vec2 &tileMapPos, ShaderProgram &shaderProgram, Player *target, BulletManager *bulletManager);
	void defeated();
	void phase1();
	void phase2();
	void phase3();
	void render();
	void setTileMap(TileMap *tileMap);
	void update(int deltaTime);

	bool stopMusic();
	bool isBossDefeated();

	glm::vec2 ret_pos();
	glm::vec2 ret_size();
	void hit();
private:

	bool isInvincible, isDefeated, isPhase1, isPhase2, isPhase3;
	int bossHealth, bossMaxHealth, cooldown, cooldownMax;
	int cutsceneDelay;
	glm::vec2 posEnemy, size;

	BulletManager *bM;
	ShaderProgram sP;
	SoundManager sM;

	Texture spritesheet, spritesheet2;
	TileMap *map;
	Sprite *bossBaseSprite, *bossMouthSprite;
};

#endif

