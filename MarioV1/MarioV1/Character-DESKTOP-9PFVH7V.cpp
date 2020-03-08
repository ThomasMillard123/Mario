#include "Character.h"
#include"Texture2D.h"
#include"Constants.h"
Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition) {
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath)) {
		std::cout << "Failed to load background texture!";
		
	}
	mPosition = startPosition;
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;

	/*mJumpForce = INITIAL_JUMP_FORCE;
	mCanJump = true;
	mJumping = false;*/

}


void Character::render() {

	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
}

void Character::MoveLeft(float deltaTime) {
	mFacingDirection = FACING_LEFT;
	mPosition.x -= MOVEMENT_SPEED;
}

void Character::MoveRight(float deltaTime) {
	mFacingDirection = FACING_RIGHT;
	mPosition.x += MOVEMENT_SPEED;
}
void Character::jump() {
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}

}

void Character::addGravity(float deltaTime) {
	if (mPosition.y < 330) {
	mPosition.y += GRAVITY * deltaTime;
	}
	else 
	{
		mCanJump = true;
	}
	
	
}
void Character::update(float deltaTime, SDL_Event e) {
	
	if (mJumping) {
		mPosition.y -= mJumpForce * deltaTime;
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
		if (mJumpForce <= 0.0f) {
			mJumping = false;
			
		}
	}
	addGravity(deltaTime);
	if (mMovingLeft) {
		MoveLeft(deltaTime);
	}
	else if (mMovingRight) {
		MoveRight(deltaTime);
	}


	switch (e.type)
	{
		//closes with press of key. This case it is q.
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			Character::jump();
			break;
		case SDLK_DOWN:
			
			break;
		case SDLK_LEFT:
		
			mMovingLeft = true;
			break;
		
		case SDLK_RIGHT:
			mMovingRight = true;
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
			mMovingRight = false;
			break;
		}
	default:
		break;
	}
}

void Character::setPosition(Vector2D newPosition) {
	mPosition = newPosition;
}

Vector2D Character::getPosition() {
	
	return mPosition;
}

Character::~Character() {
	mRenderer = NULL;

}