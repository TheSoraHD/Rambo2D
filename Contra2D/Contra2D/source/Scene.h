#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "Boss.h"
#include "Bridge.h"
#include "BulletManager.h"
#include "Enemy.h"
#include "HUD.h"
#include "MainMenu.h"
#include "Player.h"
#include "ShaderProgram.h"
#include "SoundManager.h"
#include "TileMap.h"
#include "PowerUp.h"
#include "Explosion.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(int level);
	void update(int deltaTime);
	void render();

	void checkVictory();
	void endVictory();

private:
	void initShaders();
	void initBridges();
	void initBoss();
	void initEnemies();
	void initMainMenu();
	void initPlayer();
	void initPowerUp();
	void initTransition(int level);
	void checkPowerUp();
	void checkHits();
	void checkfall();
	void checkBullets();
	void checkExplosions(int deltaTime);


private:
	BulletManager bulletManager;
	SoundManager sound;				  // Audio engine
	vector<Bullet*> activeBullets;
	vector<Explosion*> activeExplosions;

	MainMenu mainMenu;

	bool victory = false;
	bool za_warudo = false;
	bool shindeiru = false;
	int timer_za_warudo = 550;
	int timer_shindeiru = 275;
	int activeLevel, nextLevel;
	float transitionDelay;

	Boss *boss;
	Player *player;
	HUD hud;
	PowerUp *powerup;
	vector<Bridge*> bridgeList;
	vector<Enemy*> enemyList;
	ShaderProgram texProgram;
	Sprite *transition;
	Texture spritesheet;
	TileMap *map;

	float currentTime;
	glm::mat4 projection;
	vector<glm::vec2> Enemy_FirstLevel;

};


#endif // _SCENE_INCLUDE

