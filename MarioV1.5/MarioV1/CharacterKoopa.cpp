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
	
	if (!mInjured) {
		
		if (mMovingLeft) {
			MoveLeft(deltaTime);
		}
		if (mMoveingRight) {
			MoveRight(deltaTime);
		}
		
		
		//stop from charters going off screen
		if (mPosition.x >= SCREEN_WIDTH - mSingleSpriteWidth) {
			mMovingLeft = true;
			mMoveingRight = false;
			mFacingDirection = FACING_LEFT;
		}
		if (mPosition.x < 0) {
			mMovingLeft = false;
			mMoveingRight = true;
			mFacingDirection = FACING_RIGHT;
		}

		if (mFacingDirection == FACING_LEFT) {
			mMovingLeft =true;
		}
		if (mFacingDirection == FACING_RIGHT) {
			mMoveingRight = true;
		}
		
		//find map position
		int centralXPosition = (int)(mPosition.x + (mSingleSpriteWidth*0.5)) / TILE_WIDTH;
		int centralYPosition = (int)(mPosition.y + (mSingleSpriteHight * 0.5)) / TILE_HEIGHT;
		int footPosition = (int)(mPosition.y + mSingleSpriteHeight) / TILE_HEIGHT;
		int left = (int)(mPosition.x + (mSingleSpriteWidth)) / TILE_WIDTH;
		int right = (int)(mPosition.x) / TILE_WIDTH;
		if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0 || mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 3) {
			mMovingLeft = false;
			mMoveingRight = false;
			Character::AddGravity(deltaTime);
		}
		else
		{

		}
		
		if (mCurrentLevelMap->GetTileAt(centralYPosition, left) == 1) {

			mMoveingRight = false;
			mFacingDirection = FACING_LEFT;
		}
		if (mCurrentLevelMap->GetTileAt(centralYPosition, right) == 1) {

			mMovingLeft = false;
			mFacingDirection = FACING_RIGHT;
		}
		

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