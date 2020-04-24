#include "CharacterMario.h"
#include"Texture2D.h"
#include "Constants.h"
#include"LevelMap.h"
#include"SoundEffect.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map): Character(renderer, imagePath,startPosition, map)
{	
	mPosition = startPosition;
	mFacingDirection = FACING_RIGHT;
	mMoveingRight = false;
	mMovingLeft = false;
	mWalkAnimation = 0;
}


void CharacterMario::Render() {
	mSingleSpriteWidth = mTexture->GetWidth() / 16.0f;
	mSingleSpriteHight = mTexture->GetHeight() / 5;
	int yPos = mSingleSpriteHight * mSpritesheetPositionY;
	int xPos = mSingleSpriteWidth * mSpritesheetPositionX;
	SDL_Rect portionOfSpritesheet = { xPos,yPos,mSingleSpriteWidth,mSingleSpriteHight };
	SDL_Rect destRect = { (int)(mPosition.x),(int)(mPosition.y),mSingleSpriteWidth,mSingleSpriteHight};
	
	if (mFacingDirection == FACING_RIGHT) {
		mTexture->RenderSpritesheet(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->RenderSpritesheet(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}


void CharacterMario::MoveLeft(float deltaTime) {

	mFacingDirection = FACING_LEFT;
	mPosition.x -= MOVEMENTSPEED;
	if (mWalkAnimation == 0) {
		mSpritesheetPositionX = 9.5f;
	}
	else if(mWalkAnimation <=1000)
	{
		mSpritesheetPositionX = 10.9f;
	}
	else if(mWalkAnimation <=2000)
	{
		mSpritesheetPositionX = 12.0f;
	}
	else 
	{
		mWalkAnimation = 0;
		
	}
	mWalkAnimation++;
	
}

void CharacterMario::MoveRight(float deltaTime) {

	mFacingDirection = FACING_RIGHT;
	mPosition.x += MOVEMENTSPEED;
	if (mWalkAnimation == 0) {
		mSpritesheetPositionX = 9.5f;
	}
	else if (mWalkAnimation <= 1000)
	{
		mSpritesheetPositionX = 10.9f;
	}
	else if (mWalkAnimation <= 2000)
	{
		mSpritesheetPositionX = 12.0f;
	}
	else
	{
		mWalkAnimation = 0;
	}
	mWalkAnimation++;
}


void CharacterMario::Update(float deltaTime, SDL_Event e) {
	Character::Update(deltaTime, e);

	if (mMovingLeft) {
		MoveLeft(deltaTime);
	}
	else if (mMoveingRight) {
		MoveRight(deltaTime);
	}
	


	if (mCharacterState == ALIVE) {
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				mJumpSound->PlaySound();
				Character::Jump();
				break;
			case SDLK_s:
				break;
			case SDLK_a:
				mMovingLeft = true;
				break;
			case SDLK_d:
				mMoveingRight = true;
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
				mMovingLeft = false;
				break;

			case SDLK_d:
				mMoveingRight = false;
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}


CharacterMario::~CharacterMario()
{
}
