#include "Character.h"
#include"Texture2D.h"
#include "Constants.h"
#include"LevelMap.h"
#include"SoundEffect.h"
Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) {
	mRenderer = renderer;
	mScale = 10;
	mSpritesheetPositionX = 8.0f;
	mSpritesheetPositionY = 1.3f;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath)) {
		std::cout << "Failed to load background texture!";
	}

	mJumpSound = new SoundEffect();
	mJumpSound->LoadSound("SoundEffects/Jump.wav");
	mDeathSound = new SoundEffect();
	mDeathSound->LoadSound("SoundEffects/death.wav");
	mCollisionRadius = 15.0f;
	mCurrentLevelMap = map;
	
}

void Character::Update(float deltaTime, SDL_Event e) {
	//checks if charater is alive state
	if (mCharacterState == DEAD) {
		
		if (count == 0) {
			mDeathSound->PlaySound();
			mPosition.y = 500;
			count++;
		}
		
	}

	//stop from charters going off screen
	if (mPosition.x >= SCREEN_WIDTH - mSingleSpriteWidth) {
		mPosition.x = SCREEN_WIDTH - mSingleSpriteWidth;
	}
	if (mPosition.x <-6) {
		mPosition.x = 0;
	}
	
	//jump 
	if (mCanJump == true) {
		if (mJumping) {

			mPosition.y -= mJumpForce * deltaTime;
			mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

			mSpritesheetPositionX = 14.0f;
			if (mJumpForce <= 0.0f) {
				mJumping = false;
			}
		}
	}
	
	/*find map position*/
	int centralXPosition = (int)(mPosition.x + (mSingleSpriteWidth*0.5)) / TILE_WIDTH;
	int centralYPosition= (int)(mPosition.y + (mSingleSpriteHight*0.5)) / TILE_HEIGHT;
	int footPosition = (int)(mPosition.y + mSingleSpriteHight ) / TILE_HEIGHT;
	int headPosition= (int)(mPosition.y) / TILE_HEIGHT;

	int left= (int)(mPosition.x + (mSingleSpriteWidth)) / TILE_WIDTH;
	int right= (int)(mPosition.x) / TILE_WIDTH;
	//check if on a block
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0|| mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 3) {
		Character::AddGravity(deltaTime);
		
	}
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 1|| mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 2)
	{
		mCanJump = true;
		mSpritesheetPositionX = 8.0f;
	}
	//colision with bottom of the bolck
	if (mCurrentLevelMap->GetTileAt(headPosition, centralXPosition) == 1) {
		
		CancelJump();
	}
	//colision with the side of the blocks
	if (mCurrentLevelMap->GetTileAt(centralYPosition, left) == 1||mCurrentLevelMap->GetTileAt(centralYPosition, left) == 2) {
		
		mMoveingRight = false;
		
	}
	if (mCurrentLevelMap->GetTileAt(centralYPosition, right) == 1 || mCurrentLevelMap->GetTileAt(centralYPosition, right) == 2) {

		mMovingLeft = false;
		
	}
	
}
void Character::AddGravity(float deltaTime) {
	if (mPosition.y <= SCREEN_WIDTH) {
		mPosition.y += GRAVITY*deltaTime;
		

	}
	else
	{
		mCanJump = true;
	}
}

void Character::Jump() {
	
	if (!mJumping) {
		mJumpForce = INITAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}
bool Character::IsJumping() {
	return mJumping;
}

void Character::CancelJump() {
	mJumpForce = 0;
}
void Character::MoveLeft(float deltaTime) {	
}


void Character::MoveRight(float deltaTime) {
}


void Character::SetPosition(Vector2D newPosition) {
	mPosition = newPosition;
}

Vector2D Character::GetPosition() {

	return mPosition;
}

float Character::GetCollisionRadius() {
	return mCollisionRadius;

}
Rect2D Character::GetCollisionBox() {
	return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHight);

}

void Character::SetCharacterState(CHARACTERSTATE state) {
	mCharacterState = state;
}

CHARACTERSTATE Character::GetCharacterState() {
	return mCharacterState;
}

void Character::Render() {	
}

Character::~Character() {
	
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;

	delete mJumpSound;
	mJumpSound = NULL;
	delete mDeathSound;
	mDeathSound = NULL;

	delete mCurrentLevelMap;
	mCurrentLevelMap = NULL;
}