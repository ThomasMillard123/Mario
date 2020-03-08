#include "Sound.h"



Sound::Sound()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "Mixer could not initialise. Error: " << Mix_GetError();
	}
}

void Sound::LoadSound(std::string path) {
}

void Sound::PlaySound() {
}

Sound::~Sound()
{

}
