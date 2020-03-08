#pragma once
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
class PowBlock;

class GameScreenLevel1: GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();


	void Render();
	void Update(float deltaTime, SDL_Event e);

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void UpdatePowBlock();
	void DoScreenshake();
private:
	Texture2D* mBackgroundTexture;
	Character* mPlayerOne;
	Character* mPlayerTwo;
	LevelMap* mLevelMap;
	PowBlock* mPowBlock;

	Sound* mBackgroundMusic;


	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;


	vector<CharacterKoopa*> mEnemies;

	bool SetUpLevel();
	void SetLevelMap();

};

