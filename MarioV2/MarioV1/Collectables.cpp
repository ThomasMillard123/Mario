#include "Collectables.h"



Collectables::Collectables(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map)
{
	mRenderer = renderer;
	mState = true;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath)) {
		std::cout << "Failed to load background texture!";
	}

	mCurrentLevelMap = map;
}
void Collectables::Render() {

}
void Collectables::Update(float deltaTime, SDL_Event e) {

}
void Collectables::SetPosition(Vector2D newPosition) {
	mPosition = newPosition;
}

Vector2D Collectables::GetPosition() {

	return mPosition;
}

float Collectables::GetCollisionRadius() {
	return mCollisionRadius;

}
Rect2D Collectables::GetCollisionBox() {
	return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth,mSingleSpriteHeight);

}

bool Collectables::GetState() {
	return mState;
}
void Collectables::SetState(bool setState) {
	mState = setState;
}

Collectables::~Collectables()
{
	
	mRenderer = NULL;

	delete mTexture;
	mTexture = NULL;

	delete mCurrentLevelMap;
	mCurrentLevelMap = NULL;
}
