#include "Character.h"
#include"Texture2D.h"
#include "Constants.h"
#include"LevelMap.h"
#include"SoundEffect.h"
Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) {
	mRenderer = renderer;

	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath)) {
		std::cout << "Failed to load background texture!";
	}

	mJumpSound = new SoundEffect();
	mJumpSound->LoadSound("SoundEffects/Jump.wav");

	mCollisionRadius = 15.0f;
	mCurrentLevelMap = map;
}

void Character::Render() {
	
}

void Character::AddGravity(float deltaTime) {
	if (mPosition.y <= 345) {
		mPosition.y += GRAVITY /** deltaTime*/;
		mCanJump = false;
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
	return mCanJump;
}

void Character::CancelJump() {
	mJumping = false;
	

}
void Character::MoveLeft(float deltaTime) {	
}


void Character::MoveRight(float deltaTime) {
}


void Character::Update(float deltaTime, SDL_Event e) {
	
	if (mPosition.x >= SCREEN_WIDTH - mTexture->GetWidth()) {
		mPosition.x = SCREEN_WIDTH - mTexture->GetWidth();
	}
	if (mPosition.x <= 0) {
		mPosition.x = 0;
	}

	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0) {
		Character::AddGravity(deltaTime);
	}
	else
	{
		mCanJump = true;
	}
	if (mCanJump) {
		if (mJumping) {
			mPosition.y -= mJumpForce;

			mJumpForce -= JUMP_FORCE_DECREMENT;

			if (mJumpForce <= 0.0f) {
				mJumping = false;
			}
		}
	}
	else if (!mCanJump)
	{

	}

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
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());

}


Character::~Character() {
	mRenderer = NULL;

}