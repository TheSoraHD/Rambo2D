#ifndef _BULLETMANAGER_INCLUDE
#define _BULLETMANAGER_INCLUDE

#include "Bullet.h"


class BulletManager
{
public:


	void createPlayerBullet(float posPlayerx, float posPlayery, int direction, bool spreadGun, ShaderProgram &shaderProgram);
	void setTileMap(TileMap *tileMap);
	void update(int deltaTime);
	void render();
	vector<Bullet*> ret_actBullets();

private:
	vector<Bullet*> activeBullets;
	TileMap *map;
};

#endif

