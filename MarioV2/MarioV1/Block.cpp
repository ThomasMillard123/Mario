#include "Block.h"

Block::Block(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map)
{
	mRenderer = renderer;
	mPosition = startPosition;
	mStartPosition = startPosition;
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

//shake blocks
void Block::Shake(Vector2D shake) {
	mPosition.y += shake.y;
	mPosition.x += shake.x;
}
//reset the position of blocks
void Block::ResetPosition() {
	mPosition = mStartPosition;
}

Vector2D Block::GetPosition() {
	return mPosition;
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