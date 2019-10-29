#include "SoundManager.h"
using namespace irrklang;


SoundManager::SoundManager()
{
	music = NULL;
	sfx = NULL;
	// start the sound engine with default parameters
	soundEngine = createIrrKlangDevice();

}


SoundManager::~SoundManager()
{
	if (music != NULL) delete music;
	if (sfx != NULL) delete sfx;
	soundEngine->drop(); // delete engine
}


void SoundManager::playBGM(const char* filename, bool isLooped)
{
	music = soundEngine->play2D(filename, isLooped, false, true, ESM_AUTO_DETECT, true);
}


void SoundManager::stopBGM()
{
	if (music != NULL) music->stop();
}

void SoundManager::pauseBGM()
{
	if (music != NULL) music->setIsPaused(1);
}

void SoundManager::resumeBGM()
{
	if (music != NULL) music->setIsPaused(0);
}

void SoundManager::playSFX(const char* filename)
{
	sfx = soundEngine->play2D(filename);
}