#pragma once
#include "Character.h"
class LevelMap;
class CharacterKoopa :
	public Character
{
protected:
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map,FACING startFaceing,float movementSpeed);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	bool GetAlive();
	void SetAlive(bool setAlive);
private:
	FACING mFacingDirection;
	float mMovementSpeed;
	bool mMovingLeft;
	bool mMoveingRight;
	bool mAlive;
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool mInjured;
	float mInjuredTime;
	LevelMap* mCurrentLevelMap;

	void FlipRightwayUp();
	
};

