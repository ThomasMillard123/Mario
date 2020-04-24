#ifndef _HIGHSCORES_H
#define _HIGHSCORES_H

#include "GameScreen.h"
#include<SDL.h>

#include"Commons.h"
#include"LevelMap.h"
#include"Character.h"
#include"Sound.h"
#include"Buttions.h"
#include"Text.h"

class GameScreenHighScores :
	public GameScreen
{
public:
	GameScreenHighScores(SDL_Renderer* renderer);
	~GameScreenHighScores();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void OutputHightScores();
private:
	Text* mInstruction;
	Text* mScore;
	
};

#endif