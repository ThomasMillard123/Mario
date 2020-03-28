#include "Block.h"

Block::Block(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map)
{
	mRenderer = renderer;
	mPosition = startPosition;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath)) {
		std::cout << "Failed to load background texture!";
	}

	mCurrentLevelMap = map;
}
void Block::Render() {
	
	mTexture->Render(mPosition, SDL_FLIP_NONE);
}
void Block::Update(float deltaTime, SDL_Event e) {

}
void Block::Shake(Vector2D newPosition) {
	mPosition.y += newPosition.y;
}

Vector2D Block::GetPosition() {
	return mPosition;
}

float Block::GetCollisionRadius() {
	return mCollisionRadius;

}
Rect2D Block::GetCollisionBox() {
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());

}



Block::~Block()
{
	
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;

	delete mCurrentLevelMap;
	mCurrentLevelMap = NULL;
}