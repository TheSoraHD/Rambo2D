#ifndef _MAINMENU_INCLUDE
#define _MAINMENU_INCLUDE


#include "Sprite.h"
#include "SoundManager.h"

class MainMenu
{
public:
	void init(ShaderProgram &shaderProgram);
	void render();
	void update(int deltaTime);
private:
	SoundManager sound;

	bool introAnim;
	float backgroundPos;
	int cursor, inputDelay;
	Texture spritesheet, spritesheet2;
	Sprite *background, *medal;
};

#endif
