#ifndef _LEVEL1_H
#define _LEVEL1_H

#include<SDL.h>
#include<vector>

#include"Commons.h"
#include"GameScreen.h"
#include"LevelMap.h"
#include"Character.h"
#include"Sound.h"

class Texture2D;
class Character;
class CharacterKoopa;
class CollectablesCoins;
class PowBlock;

class GameScreenLevel1: GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer, int numberOfPlayers, int score);
	~GameScreenLevel1();


	void Render();
	void Update(float deltaTime, SDL_Event e);

	//updates
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdatePowBlock();
	void UpdateCoin(float deltaTime, SDL_Event e);

	//action
	void DoScreenshake();

	//creat new
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position);
private:
	//players
	Character* mPlayerOne;
	Character* mPlayerTwo;

	//enmenys
	vector<CharacterKoopa*> mEnemies;
	
	//interactables 
	PowBlock* mPowBlock;
	vector<CollectablesCoins*> mCoins;
	int mCoinCount;

	//textures
	Texture2D* Layer0;
	Texture2D* mBackgroundTexture;

	//sounds
	Sound* mBackgroundMusic;
	Sound* mCoinCollect;
	Sound* mNewLevel;

	void SetUpSounds();
	//screen shake
	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;

	//level setup
	LevelMap* mLevelMap;
	bool SetUpLevel();
	void SetLevelMap();

};

#endif


