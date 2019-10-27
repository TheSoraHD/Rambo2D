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

#define INIT_ENEMY_X_TILES 2
#define INIT_ENEMY_Y_TILES 3

Scene::Scene()
{
	map = NULL;
	player = NULL;
	enemy = NULL;
	for (int i = 0; i < bridgeList.size(); ++i)
		bridgeList[i] = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if (enemy != NULL)
		delete enemy;
	if (bridgeList.size() != NULL) {
		for (int i = 0; i < bridgeList.size(); ++i)
			bridgeList[i] = NULL;
	}
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
	enemy = new Enemy();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, player);
	enemy->setTileMap(map);
	enemy->setPosition(glm::vec2(INIT_ENEMY_X_TILES * map->getTileSize(), INIT_ENEMY_Y_TILES * map->getTileSize()));
	initBridges();
	BulletManager::instance().setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	BulletManager::instance().update();
	player->update(deltaTime);
	enemy->update(deltaTime);
	for (int i = 0; i < bridgeList.size(); ++i)
		bridgeList[i]->update(deltaTime);
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
	enemy->render();
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
				bridge_aux->setTileMap(map);
				bridge_aux->init(3, glm::ivec2(2, 3), texProgram);
				break;
		}
		bridgeList.push_back(bridge_aux);
	}
}



