#include "CharacterLuigi.h"
#include"Texture2D.h"
#include "Constants.h"
#include"LevelMap.h"


CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer,  imagePath, startPosition, map)
{
	mPosition = startPosition;
	mFacingDirection = FACING_LEFT;
	mMoveingRight = false;
	mMovingLeft = false;
	mCollisionRadius = 15.0f;
	
}
void CharacterLuigi::Render() {
	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
}
void CharacterLuigi::MoveLeft(float deltaTime) {

	mFacingDirection = FACING_LEFT;
	mPosition.x -= MOVEMENTSPEED;
}


void CharacterLuigi::MoveRight(float deltaTime) {

	mFacingDirection = FACING_RIGHT;
	mPosition.x += MOVEMENTSPEED;
}


void CharacterLuigi::Update(float deltaTime, SDL_Event e) {
	Character::Update(deltaTime, e);
	
	if (mMovingLeft) {
		MoveLeft(deltaTime);
	}
	else if (mMoveingRight) {
		MoveRight(deltaTime);
	}
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			mJumpSound->PlaySound();
			Character::Jump();
			break;
		case SDLK_DOWN:
			break;
		case SDLK_LEFT:
			mMovingLeft = true;
			break;
		case SDLK_RIGHT:
			mMoveingRight = true;
			break;
		default:
			break;
		}
		break;
		
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:

			mMovingLeft = false;
			break;

		case SDLK_RIGHT:

			mMoveingRight = false;
			break;
		default:
			break;
		}
	default:
		break;
	}
}

CharacterLuigi::~CharacterLuigi()
{
}
