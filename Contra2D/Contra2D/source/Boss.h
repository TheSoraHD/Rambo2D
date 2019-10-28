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
	void intro();
	void phase1();
	void phase2();
	void phase3();
	void render();
	void setTileMap(TileMap *tileMap);
	void update(int deltaTime);

	bool isBossDefeated();
private:

	bool isInvincible, isDefeated;
	int bossHealth, leftHealth, rightHealth;
	int cutsceneDelay;

	BulletManager *bM;
	SoundManager sound;

	Texture spritesheet;
	TileMap *map;
	Sprite *bossBaseSprite;
};

#endif
