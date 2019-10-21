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


void SoundManager::playBGM(const char* filename)
{
	music = soundEngine->play2D(filename, true, false, true, ESM_AUTO_DETECT, true);
}


void SoundManager::stopBGM()
{
	if (music) music->drop();
}

void SoundManager::playSFX(const char* filename)
{
	music = soundEngine->play2D(filename);
}