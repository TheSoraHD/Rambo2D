#ifndef _SOUNDMANAGER_INCLUDE
#define _SOUNDMANAGER_INCLUDE

#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	void playBGM(const char* filename, bool isLooped);
	void stopBGM();
	void pauseBGM();
	void resumeBGM();
	void playSFX(const char* filename);

private:
	irrklang::ISoundEngine* soundEngine;
	irrklang::ISound* music;
	irrklang::ISound* sfx;
};

#endif