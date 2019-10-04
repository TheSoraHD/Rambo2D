#include <iostream>
#include "Scene.h"


Scene::Scene()
{
	circle = NULL;
}

Scene::~Scene()
{
	if(circle != NULL) delete circle;
}


void Scene::init()
{
	initShaders();
	circle = Circle::createCircle(0.0f, 0.0f, 0.5f, 0.5f, program);
}

void Scene::update(int deltaTime)
{
}

void Scene::render()
{
	program.use();
	circle->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	program.init();
	program.addShader(vShader);
	program.addShader(fShader);
	program.link();
	if(!program.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << program.log() << endl << endl;
	}
	program.bindFragmentOutput("outColor");
}

