#include "SoundMusic.h"



SoundMusic::SoundMusic():Sound(){
	mBackgroundMusic = NULL;
}
void SoundMusic::LoadSound(std::string path) {
	mBackgroundMusic = Mix_LoadMUS(path.c_str());
	if (mBackgroundMusic == NULL) {
		std::cout << "Failed to load background music! Error:" << Mix_GetError() << std::endl;
	}
}
void SoundMusic::PlaySound() {

	//If there is no music playing
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(mBackgroundMusic, -1);

	}

}

SoundMusic::~SoundMusic()
{
	Mix_FreeMusic(mBackgroundMusic);
	mBackgroundMusic = NULL;
}
