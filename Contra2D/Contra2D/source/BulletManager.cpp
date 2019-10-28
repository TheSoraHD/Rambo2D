#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "BulletManager.h"
#include "Scene.h"

enum SpreadDeviation {
	DEVIATION_1L, DEVIATION_2L, NO_DEVIATION, DEVIATION_1R, DEVIATION_2R
};


void BulletManager::createPlayerBullet(float posPlayerx, float posPlayery, int direction, bool spreadGun, ShaderProgram &shaderProgram) {
	Bullet* new_bull;
	new_bull = new Bullet;
	new_bull->setTileMap(map);
	new_bull->createBullet(posPlayerx, posPlayery, direction, spreadGun, NO_DEVIATION, 1, shaderProgram);
	activeBullets.emplace_back(new_bull);
	if (spreadGun) {
		new_bull = new Bullet;
		new_bull->setTileMap(map);
		new_bull->createBullet(posPlayerx, posPlayery, direction, spreadGun, DEVIATION_1L, 1, shaderProgram);
		activeBullets.emplace_back(new_bull);

		new_bull = new Bullet;
		new_bull->setTileMap(map);
		new_bull->createBullet(posPlayerx, posPlayery, direction, spreadGun, DEVIATION_2L, 1, shaderProgram);
		activeBullets.emplace_back(new_bull);

		new_bull = new Bullet;
		new_bull->setTileMap(map);
		new_bull->createBullet(posPlayerx, posPlayery, direction, spreadGun, DEVIATION_1R, 1, shaderProgram);
		activeBullets.emplace_back(new_bull);

		new_bull = new Bullet;
		new_bull->setTileMap(map);
		new_bull->createBullet(posPlayerx, posPlayery, direction, spreadGun, DEVIATION_2R, 1, shaderProgram);
		activeBullets.emplace_back(new_bull);
	}
}

void BulletManager::update(int deltaTime, vector<Enemy*> enemyList) {
	for (int j = 0; j < int(enemyList.size()); ++j) {
		for (int i = 0; i < int(activeBullets.size()); ++i) {
			//colision en las X
			activeBullets[i]->update(deltaTime);
			bool collisionX = (((enemyList[j]->ret_pos.x + enemyList[j]->ret_size.x) >= activeBullets[i]->ret_pos.x) &&
								((activeBullets[i]->ret_pos.x + activeBullets[i]->ret_size.x) >= enemyList[j]->ret_pos.x));
			//colision en las Y
			bool collisionY = (((enemyList[j]->ret_pos.y + enemyList[j]->ret_size.y) >= activeBullets[i]->ret_pos.y) &&
				((activeBullets[i]->ret_pos.y + activeBullets[i]->ret_size.y) >= enemyList[j]->ret_pos.y));

			if (collisionX && collisionY) {
				enemyList[j]->hit();
				activeBullets[i]->~Bullet();
			}
		}
	}
}

void BulletManager::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void BulletManager::render() {
	for (int i = 0; i < int(activeBullets.size()); ++i) {
		activeBullets[i]->render();
	}
}


