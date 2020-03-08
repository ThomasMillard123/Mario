#pragma once
#include<SDL.h>
#include"Commons.h"
#include"GameScreen.h"


class Texture2D;
class Character;

class GameScreenLevel1: GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();


	void render();
	void update(float deltaTime, SDL_Event e);
private:
	Texture2D* mBackgroundTexture;
	Character* myCharacter;

	bool setUpLevel();
};

