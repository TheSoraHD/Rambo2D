#ifndef _BULLETMANAGER_INCLUDE
#define _BULLETMANAGER_INCLUDE

#include "Bullet.h"


class BulletManager
{
public:


	void createPlayerBullet(float posPlayerx, float posPlayery, int direction, ShaderProgram &shaderProgram);
	void setTileMap(TileMap *tileMap);
	void update(int deltaTime);
	void render();
private:
	vector<Bullet*> activeBullets;
	TileMap *map;
};

#endif

