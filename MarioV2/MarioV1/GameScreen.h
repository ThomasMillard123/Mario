#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H


#include<SDL.h>
#include<string>
#include<vector>

#include"Commons.h"
#include"Text.h"
#include"Texture2D.h"
#include"Sound.h"
#include"Character.h"
#include"LevelMap.h"
class CollectablesCoins;
class PowBlock;
class CharacterKoopa;

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
	
	//enmenys
	vector<CharacterKoopa*> mEnemies;

	//players
	Character* mPlayerOne;
	Character* mPlayerTwo;

	//textures
	Texture2D* Layer0;

	//sounds
	Sound* mBackgroundMusic;
	Sound* mCoinCollect;
	Sound* mNewLevel;

	//interactables 
	PowBlock* mPowBlock;
	vector<CollectablesCoins*> mCoins;
	int mCoinCount;
	int mNumberOfCoins;

	//level setup
	LevelMap* mLevelMap;
	
	//screen shake
	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;

};

#endif
