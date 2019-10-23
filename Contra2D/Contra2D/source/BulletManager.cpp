#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "BulletManager.h"
#include "Scene.h"

vector<Bullet> activeBullets;

enum directions //0, 1, 2, 3
{
	LEFT, RIGHT, UP, DOWN
};

void BulletManager::createPlayerBullet(float posPlayerx, float posPlayery, int direction, ShaderProgram &shaderProgram) {
	Bullet new_bull;
	new_bull.createBullet(posPlayerx, posPlayery, direction, 1, shaderProgram);
	activeBullets.push_back(new_bull);
}

void BulletManager::update() {
	for (int i = 0; i < int(activeBullets.size()); ++i) {
		activeBullets[i].update();
	}
}


