#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "Bridge.h"
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "SoundManager.h"
#include "Enemy.h"


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

private:
	void initShaders();
	void initBridges();
	void initEnemies();

private:
	SoundManager sound;				  // Audio engine

	TileMap *map;
	Player *player;
	vector<Bridge*> bridgeList;
	Enemy *enemy;
	Enemy *enemy_aux;
	vector<Enemy*> enemyList;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	vector<glm::vec2> Enemy_FirstLevel;

};


#endif // _SCENE_INCLUDE

