#ifndef _CHARACTER_H
#define _CHARACTER_H

#include<iostream>
#include"Commons.h"
#include<SDL.h>
#include"Sound.h"
using namespace std;

class Texture2D;
class LevelMap;
class Character
{
protected:
	int count;
	SDL_Renderer* mRenderer;
	LevelMap* mCurrentLevelMap;
	//Character infromation
	Vector2D mPosition;
	Texture2D* mTexture;
	int mSingleSpriteWidth, mSingleSpriteHight,mScale;
	float mSpritesheetPositionX, mSpritesheetPositionY;
	bool mJumping;
	bool mCanJump;
	float mJumpForce;
	bool mMovingLeft;
	bool mMoveingRight;
	CHARACTERSTATE mCharacterState;
	float mCollisionRadius;
	//sounds
	Sound* mJumpSound;
	Sound* mDeathSound;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	//posiotion infromation
	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	//Collision infromation
	float GetCollisionRadius();
	Rect2D GetCollisionBox();
	
	void SetCharacterState(CHARACTERSTATE state);
	CHARACTERSTATE GetCharacterState();

	//jump and gravity
	void AddGravity(float deltaTime);
	void Jump();
	bool IsJumping();
	void CancelJump();


};

#endif

