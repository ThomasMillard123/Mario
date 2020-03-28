#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H


#include<SDL.h>
#include<string>
#include"Commons.h"
#include"Text.h"
#include"Texture2D.h"

class GameScreen
{
public:

	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	bool GetGameState();
	SCREENS GetNextScreen();
	int GetNumberOfPlayers();
	int GetScore();
protected:
	SDL_Renderer* mRenderer;
	bool mGameEnd;
	SCREENS mNextScreen;
	int mNumberOfPlayers;
	int mScore;
	std::string mLeveLHUD;
	Text* mHUD;
	Texture2D* mSpriteSheet;
};

#endif
