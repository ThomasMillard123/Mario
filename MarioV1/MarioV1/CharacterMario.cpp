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
	
}


void CharacterMario::Render() {
	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
}


void CharacterMario::MoveLeft(float deltaTime) {

	mFacingDirection = FACING_LEFT;
	mPosition.x -= MOVEMENTSPEED;
}

void CharacterMario::MoveRight(float deltaTime) {

	mFacingDirection = FACING_RIGHT;
	mPosition.x += MOVEMENTSPEED;
}


void CharacterMario::Update(float deltaTime, SDL_Event e) {
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
		//closes with press of key. This case it is q.
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


CharacterMario::~CharacterMario()
{

}
