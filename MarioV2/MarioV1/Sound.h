
#ifndef _SOUND_H
#define _SOUND_H

#include<SDL_image.h>
#include<SDL_mixer.h>
#include<iostream>
#include<string>
#include<SDL.h>

#include"Constants.h"
#include"Texture2D.h"
#include"Commons.h"
#include"Sound.h"

class Sound
{
public:
	Sound();
	~Sound();

	virtual void LoadSound(std::string path);
	virtual void PlaySound();
	virtual void PauseSound();
};

#endif