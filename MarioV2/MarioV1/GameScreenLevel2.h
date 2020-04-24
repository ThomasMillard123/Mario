#ifndef _LEVEL2_H
#define _LEVEL2_H

#include<SDL.h>


#include"Commons.h"
#include"GameScreen.h"

#include"Character.h"
#include"Block.h"
class Texture2D;

class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2(SDL_Renderer* renderer, int numberOfPlayers, int score);
	~GameScreenLevel2();


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
	void CreateBlock(Vector2D position);
	void CreatePipe(Vector2D position,FACING faceingDirection);
	void CreatPowBlock(Vector2D position);
private:
	


	//map blocks
	vector<Block*> mBlocks;

	void SetUpSounds();

	
	bool SetUpLevel();
	void SetLevelMap();
	
};

#endif