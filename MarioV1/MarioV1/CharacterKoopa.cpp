#include "CharacterKoopa.h"
#include"Texture2D.h"
#include "Constants.h"
#include"LevelMap.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map,FACING startFaceing, float movementSpeed):Character(renderer, imagePath, startPosition, map){
	mPosition = startPosition;
	mMovementSpeed = movementSpeed;
	mFacingDirection = startFaceing;
	
	mInjured = false;
	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();
	mAlive = true;

}

void CharacterKoopa::TakeDamage() {
	mInjured = true;
	mInjuredTime = KOOPA_INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump() {
	if (!mJumping) {
		mJumpForce = INITAL_JUMP_FORCE_SMALL;
		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::FlipRightwayUp() {
	mFacingDirection = FACING_RIGHT;
	mInjured = false;
	Jump();
}
void CharacterKoopa::Render() {
	int left = 0.0f;

	if (mInjured) {
		left = mSingleSpriteWidth;
	}

	SDL_Rect portionOfSpritesheet = { left,0,mSingleSpriteWidth,mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x),(int)(mPosition.y),mSingleSpriteWidth,mSingleSpriteHeight };
	if (mFacingDirection == FACING_RIGHT) {
		mTexture->RenderSpritesheet(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else {
		mTexture->RenderSpritesheet(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

bool CharacterKoopa::GetAlive() {
	return mAlive;
}

void CharacterKoopa::SetAlive(bool setAlive) {
	mAlive = setAlive;
}
void CharacterKoopa::MoveLeft(float deltaTime) {

	mFacingDirection = FACING_LEFT;
	mPosition.x -= mMovementSpeed;
	
}


void CharacterKoopa::MoveRight(float deltaTime) {
	mFacingDirection = FACING_RIGHT;
	mPosition.x += mMovementSpeed;
}
void CharacterKoopa::Update(float deltaTime, SDL_Event e) {
	Character::Update(deltaTime, e);

	if (!mInjured) {
		if (mFacingDirection == FACING_LEFT) {
			mMovingLeft == true;
			mMoveingRight == false;

		}
		else if (mFacingDirection == FACING_RIGHT) {
			mMoveingRight = true;
			mMovingLeft = false;
		}
		/*if (mMovingLeft) {
		moveLeft(deltaTime);
		}
		else if (mMoveingRight) {
		moveRight(deltaTime);
		}*/
	}
	else {
		mMoveingRight = false;
		mMovingLeft = false;
		mInjuredTime -= deltaTime;
		if (mInjuredTime <= 0.0) {
			FlipRightwayUp();
		}

	}

}

CharacterKoopa::~CharacterKoopa() {


}