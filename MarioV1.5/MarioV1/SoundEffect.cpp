#include "SoundEffect.h"



SoundEffect::SoundEffect():Sound(){
	mSoundEffect = NULL;
}

void SoundEffect::LoadSound(std::string path) {
	mSoundEffect = Mix_LoadWAV(path.c_str());
	if (mSoundEffect == NULL) {
		std::cout << "Failed to load sound effect! Error:" << Mix_GetError() << std::endl;
	}
}


void SoundEffect::PlaySound(){
	
	//play sound effect at next open channle;
	Mix_PlayChannel(-1, mSoundEffect, 0);
	
}
void SoundEffect::PuaseSoundEffect() {
	Mix_ExpireChannel(-1, 800);
}

SoundEffect::~SoundEffect()
{
	
	Mix_FreeChunk(mSoundEffect);
	mSoundEffect = NULL;
}
