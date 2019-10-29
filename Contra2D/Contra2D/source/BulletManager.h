#ifndef _BULLETMANAGER_INCLUDE
#define _BULLETMANAGER_INCLUDE

#include "Bullet.h"


class BulletManager
{
public:
	void createPlayerBullet(float posPlayerx, float posPlayery, int direction, bool spreadGun, ShaderProgram &shaderProgram);
	void createEnemyBullet(float posEnemyx, float posEnemyy, int direction, bool spreadGun, ShaderProgram &shaderProgram, float speed);
	void setTileMap(TileMap *tileMap);
	void update(int deltaTime);
	void render();

	void set_actBullets(vector<Bullet*> bullets);
	vector<Bullet*> ret_actBullets();


private:
	vector<Bullet*> activeBullets;
	TileMap *map;
};

#endif

