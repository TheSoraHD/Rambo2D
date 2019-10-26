#include "Bullet.h"


class BulletManager
{
public:

	static BulletManager &instance()
	{
		static BulletManager B;

		return B;
	}

	void createPlayerBullet(float posPlayerx, float posPlayery, int direction, ShaderProgram &shaderProgram);
	void setTileMap(TileMap *tileMap);
	void update();
	void render();
private:
	TileMap *map;
};

