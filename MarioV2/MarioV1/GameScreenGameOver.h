#ifndef _GAMEOVER_H
#define _GAMEOVER_H

#include "GameScreen.h"
#include<SDL.h>


#include"Commons.h"

#include"LevelMap.h"
#include"Character.h"
#include"Sound.h"
#include"Buttions.h"
#include"Text.h";

class GameScreenGameOver :
	public GameScreen
{
public:
	GameScreenGameOver(SDL_Renderer* renderer, int score);
	~GameScreenGameOver();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdateHightScores();
private:
	Text* mInstruction;
	Text* mScore;
	int mScoreInt;
	Text* mName;
	string mNameText;


	

};

#endif