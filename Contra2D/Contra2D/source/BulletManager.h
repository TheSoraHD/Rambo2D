#ifndef _BULLETMANAGER_INCLUDE
#define _BULLETMANAGER_INCLUDE

#include "Bullet.h"
#include "Enemy.h"

class BulletManager
{
public:
	void createPlayerBullet(float posPlayerx, float posPlayery, int direction, bool spreadGun, ShaderProgram &shaderProgram);
	void setTileMap(TileMap *tileMap);
	void update(int deltaTime, vector<Enemy*> enemyList);
	void render();

private:
	vector<Bullet*> activeBullets;
	TileMap *map;
};

#endif

