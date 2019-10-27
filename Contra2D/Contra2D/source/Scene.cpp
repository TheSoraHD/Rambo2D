#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "BulletManager.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES 2

#define TURRET 0
#define SOLDIER_KAMIKAZE 1
#define SOLDIER_GROUND 2

Scene::Scene()
{
	map = NULL;
	player = NULL;
	for (int i = 0; i < bridgeList.size(); ++i)
		bridgeList[i] = NULL;
	for (int i = 0; i < enemyList.size(); ++i)
		enemyList[i] = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if (bridgeList.size() != NULL) {
		for (int i = 0; i < bridgeList.size(); ++i)
			bridgeList[i] = NULL;
	}
	if (enemyList.size() != NULL)
		for (int i = 0; i < enemyList.size(); ++i)
			enemyList[i] = NULL;
}


void Scene::init(int level)
{
	initShaders();
	switch (level)
	{
		case 0: {
			//map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), &texProgram);
			//sound.playBGM("music/stage1.mp3");
			break;
		}
		case 1: {
			map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), &texProgram);
			sound.playBGM("music/stage1.mp3");
			break;
		}
		case 2: {
			map = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y), &texProgram);
			sound.playBGM("music/stage2.mp3");
			break;
		}
		case 3: {
			map = TileMap::createTileMap("levels/level03.txt", glm::vec2(SCREEN_X, SCREEN_Y), &texProgram);
			sound.playBGM("music/stage3.mp3");
			break;
		}
	}
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setTileMap(map);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	//initBridges();
	initEnemies();
	BulletManager::instance().setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	BulletManager::instance().update();
	player->update(deltaTime);
	for (int i = 0; i < bridgeList.size(); i++)
		bridgeList[i]->update(deltaTime);
	for (int i = 0; i < enemyList.size(); ++i)
		enemyList[i]->update(deltaTime); //TODO eliminar enemigo si se sale del scroll
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
	for (int i = 0; i < enemyList.size(); ++i)
		enemyList[i]->render();
	for (int i = 0; i < bridgeList.size(); ++i)
		bridgeList[i]->render();
	BulletManager::instance().render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Scene::initBridges() {
	int number_of_bridges = 1;
	for (int i = 0; i < number_of_bridges; ++i) {
		Bridge *bridge_aux;
		bridge_aux = new Bridge();
		switch (i) {
			case 0:
				bridge_aux->init(3, glm::ivec2(2, 3), texProgram);
				bridge_aux->setTileMap(map);
				break;
		}
		bridgeList.push_back(bridge_aux);
	}
}

void Scene::initEnemies() {
	int number_of_enemies = 11; //cuantos enemigos hay en el nivel
	for (int i = 0; i < number_of_enemies; ++i) {
		int enemy_x;
		int enemy_y;
		int typeofEnemy;
		switch (i+1) { //enemy_list
			case 1:
				enemy_x = 10; enemy_y = 5; typeofEnemy = TURRET;//PRIZE
				break;
			case 2:
				enemy_x = 40; enemy_y = 5; typeofEnemy = TURRET;
				break;
			case 3:
				enemy_x = 50; enemy_y = 5; typeofEnemy = TURRET;//PRIZE
				break;
			case 4:
				enemy_x = 52; enemy_y = 4; typeofEnemy = TURRET;
				break;
			case 5:
				enemy_x = 58; enemy_y = 4; typeofEnemy = TURRET;
				break;
			case 6:
				enemy_x = 65; enemy_y = 5; typeofEnemy = TURRET;
				break;
			case 7:
				enemy_x = 69; enemy_y = 2; typeofEnemy = TURRET;
				break;
			case 8:
				enemy_x = 72; enemy_y = 6; typeofEnemy = TURRET;//PRIZE
				break;
			case 9:
				enemy_x = 94; enemy_y = 6; typeofEnemy = TURRET;
				break;
			case 10:
				enemy_x = 98; enemy_y = 6; typeofEnemy = TURRET;
				break;
			case 11:
				enemy_x = 5; enemy_y = 3; typeofEnemy = SOLDIER_GROUND;
				break;
		}
		Enemy *enemy_aux;
		enemy_aux = new Enemy();
		enemy_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, player, typeofEnemy);
		enemy_aux->setTileMap(map);
		enemy_aux->setPosition(glm::vec2(enemy_x * map->getTileSize(), enemy_y * map->getTileSize()));
		enemyList.push_back(enemy_aux);
	}
	
}


