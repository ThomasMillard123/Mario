#pragma once
#pragma once
#include<SDL.h>
#include"Commons.h"
#include"GameScreen.h"

class Texture2D;


class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();


	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	Texture2D* mBackgroundTexture;

	bool SetUpLevel();
};
