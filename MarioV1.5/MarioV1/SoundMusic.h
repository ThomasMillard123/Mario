#ifndef _SOUNDMUSIC_H
#define __SOUNDMUSIC_H

#include "Sound.h"

class SoundMusic :
	public Sound
{
public:
	SoundMusic();
	~SoundMusic();

	void LoadSound(std::string path);
	void PlaySound();
	void PauseSound();
private:
	Mix_Music* mBackgroundMusic;
};


#endif