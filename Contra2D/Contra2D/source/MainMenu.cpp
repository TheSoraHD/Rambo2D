#include "MainMenu.h"
#include "Game.h"
#include <GL/glut.h>

void MainMenu::init(ShaderProgram &shaderProgram) {
	spritesheet.loadFromFile("images/contramainmenu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(glm::ivec2(704, 512), glm::vec2(1.0f, 1.0f), &spritesheet, &shaderProgram);
	background->setPosition(glm::vec2(704.0f,0.0f));
	spritesheet2.loadFromFile("images/medals2x.png", TEXTURE_PIXEL_FORMAT_RGBA);
	medal = Sprite::createSprite(glm::ivec2(22, 32), glm::vec2(0.5f, 1.0f), &spritesheet2, &shaderProgram);
	medal->setPosition(glm::vec2(100.0f, 614.0f));
	spritesheet3.loadFromFile("images/instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	instructions = Sprite::createSprite(glm::ivec2(704, 512), glm::vec2(1.0f, 1.0f), &spritesheet3, &shaderProgram);
	instructions->setPosition(glm::vec2(10000.0f, 0.0f));
	backgroundPos = 704.0f;
	cursor = 0;
	inputDelay = 180;
	introAnim = true;
}

void MainMenu::render() {
	background->render();
	medal->render();
	instructions->render();
}

void MainMenu::update(int deltaTime) {
	background->update(deltaTime);
	medal->update(deltaTime);
	instructions->update(deltaTime);
	if (inputDelay <= 0) {
		if (Game::instance().getSpecialKey(GLUT_KEY_UP) && cursor != 3) {
			if (cursor <= 0) cursor = 0;
			else {
				cursor--;
				inputDelay = 12;
				sound.playSFX("sfx/select.wav");
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && cursor != 3) {
			if (cursor >= 2) cursor = 2;
			else {
				cursor++;
				inputDelay = 12;
				sound.playSFX("sfx/select.wav");
			}
		}
		else if ((Game::instance().getKey('z') || Game::instance().getKey('Z'))) {
			switch (cursor) {
			case 0:	//PLAY
				sound.stopBGM();
				Game::instance().loadLevel(11);
				break;
			case 1: //INSTRUCTIONS
				sound.playSFX("sfx/select.wav");
				cursor = 3;
				inputDelay = 15;
				instructions->setPosition(glm::vec2(0.0f, 0.0f)); //Show Instructions
				break;
			case 2: //EXIT
				exit(0);
				break;
			case 3: //INSTRUCTIONS MENU
				sound.playSFX("sfx/select.wav");
				cursor = 1;
				inputDelay = 15;
				instructions->setPosition(glm::vec2(10000.0f, 0.0f)); //Hide Instructions
				break;
			}
		}
		medal->setPosition(glm::vec2(110.0f, 312.0f + cursor * 36.0f));
	}
	if (introAnim) {
		if (backgroundPos > 0)
			backgroundPos = backgroundPos - float(0.25f * deltaTime);
		else
			introAnim = false;
		background->setPosition(glm::vec2(backgroundPos, 0.0f));
	}
	inputDelay--;
}
