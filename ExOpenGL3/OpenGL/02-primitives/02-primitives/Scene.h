#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include "ShaderProgram.h"
#include "Circle.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	Circle *circle;
	ShaderProgram program;

};


#endif // _SCENE_INCLUDE

