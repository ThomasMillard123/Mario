#ifndef _SOUNDEFFECT_H
#define _SOUNDEFFECT_H

#include"Sound.h"

class SoundEffect:public Sound
{
public:
	SoundEffect();
	~SoundEffect();

	void LoadSound(std::string path);
	virtual void PlaySound();

private:
	Mix_Chunk* mSoundEffect;
};

#endif