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
	boss = NULL;
	map = NULL;
	player = NULL;
	for (int i = 0; i < int(bridgeList.size()); ++i)
		bridgeList[i] = NULL;
	for (int i = 0; i < int(enemyList.size()); ++i)
		enemyList[i] = NULL;
	transition = NULL;
}

Scene::~Scene()
{
	if (boss != NULL)
		delete boss;
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if (bridgeList.size() != NULL) {
		for (int i = 0; i < int(bridgeList.size()); ++i)
			bridgeList[i] = NULL;
	}
	if (enemyList.size() != NULL)
		for (int i = 0; i < int(enemyList.size()); ++i)
			enemyList[i] = NULL;
	if (transition != NULL)
		delete transition;
}


void Scene::init(int level)
{
	initShaders();
	switch (level)
	{
		case 0: {
			initMainMenu();
			break;
		}
		case 1: {
			map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), &texProgram);
			sound.playBGM("music/stage1.mp3", true);
			break;
		}
		case 2: {
			map = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y), &texProgram);
			sound.playBGM("music/stage2.mp3", true);
			break;
		}
		case 3: {
			map = TileMap::createTileMap("levels/level03.txt", glm::vec2(SCREEN_X, SCREEN_Y), &texProgram);
			sound.playBGM("music/stage3.mp3", true);
			break;
		}
		case 11: {
			initTransition(1);
			break;
		}
		case 12: {
			initTransition(2);
			break;
		}
		case 13: {
			initTransition(3);
			break;
		}
		case 14: {
			initTransition(0);
			break;
		}
	}
	if (level != 0 && level < 10) {
		bulletManager.setTileMap(map);
		//initBridges();
		initEnemies();
		initPlayer();
	}
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	activeLevel = level;
}

void Scene::checkVictory() {
	switch (activeLevel){
		case 1: //END REACHED
			if (player->sharePosition().x >= map->getLevelWidth() - 128.0f) endVictory();
			break;
		case 2: //ALL ENEMIES DEAD
			if (enemyList.size() == 0) endVictory();
			break;
		case 3: //BOSS DEFEATED
			if (boss != NULL && boss->isBossDefeated()) endVictory();
			break;
	}
}

void Scene::endVictory()
{
	sound.stopBGM();
	sound.playBGM("music/stageclear.mp3", false);
	victory = true;
	transitionDelay = 400;
	nextLevel = activeLevel + 11;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (activeLevel > 10 || victory) {
		transitionDelay -= deltaTime * 0.1f;
		if (transitionDelay <= 0)
			Game::instance().loadLevel(nextLevel);
	}
	else if (activeLevel != 0) {
		bulletManager.update(deltaTime);
		for (int i = 0; i < int(bridgeList.size()); i++)
			bridgeList[i]->update(deltaTime);
		for (int i = 0; i < int(enemyList.size()); ++i)
			enemyList[i]->update(deltaTime); //TODO eliminar enemigo si se sale del scroll
		if (boss != NULL) boss->update(deltaTime);
		player->update(deltaTime);
		if (!victory) checkVictory();
	}
	else mainMenu.update(deltaTime);
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
	if (activeLevel > 10 && transition != NULL) transition->render();
	else if (activeLevel != 0) {
		map->render();
		for (int i = 0; i < int(enemyList.size()); ++i)
			enemyList[i]->render();
		for (int i = 0; i < int(bridgeList.size()); ++i)
			bridgeList[i]->render();
		if (boss != NULL) boss->render();
		player->render();
		bulletManager.render();
	}
	else mainMenu.render();
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

void Scene::initBoss() {
	boss = new Boss();
	boss->setTileMap(map);
	boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, player, &bulletManager);
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
		enemy_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, player, typeofEnemy, &bulletManager);
		enemy_aux->setTileMap(map);
		enemy_aux->setPosition(glm::vec2(enemy_x * map->getTileSize(), enemy_y * map->getTileSize()));
		enemyList.push_back(enemy_aux);
	}
}

void Scene::initMainMenu() {
	mainMenu.init(texProgram);
	sound.playBGM("music/title.mp3", false);
}

void Scene::initTransition(int level) {
	switch (level){
		case 0:
			spritesheet.loadFromFile("images/ending.png", TEXTURE_PIXEL_FORMAT_RGBA);
			transitionDelay = 600;
			break;
		case 1:
			spritesheet.loadFromFile("images/transition1.png", TEXTURE_PIXEL_FORMAT_RGBA);
			transitionDelay = 180;
			break;
		case 2:
			spritesheet.loadFromFile("images/transition2.png", TEXTURE_PIXEL_FORMAT_RGBA);
			transitionDelay = 180;
			break;
		case 3:
			spritesheet.loadFromFile("images/transition3.png", TEXTURE_PIXEL_FORMAT_RGBA);
			transitionDelay = 180;
			break;
	}
	nextLevel = level;
	transition = Sprite::createSprite(glm::ivec2(704, 512), glm::vec2(1.0f, 1.0f), &spritesheet, &texProgram);
	transition->setPosition(glm::vec2(0.0f, 0.0f));
}

void Scene::initPlayer() {
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, &bulletManager);
	player->setTileMap(map);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
}


