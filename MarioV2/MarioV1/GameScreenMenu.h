#ifndef _MAINMENU_H
#define _MAINMENU_H

#include "GameScreen.h"

#include<SDL.h>


#include"Commons.h"
#include"GameScreen.h"
#include"LevelMap.h"
#include"Character.h"
#include"Sound.h"
#include"Buttions.h"
#include"Text.h";
class GameScreenMenu :
	public GameScreen
{
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Buttions* m1PlayerPlay;
	Buttions * m2PlayerPlay;
	Text* mHighScore;
	Texture2D* mTitleTexture;
	Vector2D mHighScorePos;
};

#endif
