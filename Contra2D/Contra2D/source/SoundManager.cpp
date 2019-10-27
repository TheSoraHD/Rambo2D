#include "SoundManager.h"
using namespace irrklang;


SoundManager::SoundManager()
{
	// start the sound engine with default parameters
	soundEngine = createIrrKlangDevice();

}


SoundManager::~SoundManager()
{
	soundEngine->drop(); // delete engine
}


void SoundManager::playBGM(const char* filename, bool isLooped)
{
	music = soundEngine->play2D(filename, isLooped, false, true, ESM_AUTO_DETECT, true);
}


void SoundManager::stopBGM()
{
	if (music != NULL) music->drop();
}

void SoundManager::playSFX(const char* filename)
{
	music = soundEngine->play2D(filename);
}