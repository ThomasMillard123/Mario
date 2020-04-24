#include "CollectablesCoins.h"



CollectablesCoins::CollectablesCoins(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map):Collectables(renderer,imagePath,startPosition,map)
{
	mPosition = startPosition;
	mRotation = 0;
	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	
}
void CollectablesCoins::Render() {
	
	float xPos= mSingleSpriteWidth*mRotation;
	SDL_Rect portionOfSpritesheet = { xPos,0,mSingleSpriteWidth,mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x),(int)(mPosition.y),mSingleSpriteWidth,mSingleSpriteHeight };
	mTexture->RenderSpritesheet(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	
	
}
void CollectablesCoins::Update(float deltaTime, SDL_Event e) {
	//coin animation
	if (mRotation == 3) {
		mRotation = 0;
	}
	else {
		mRotation += 1;
	}
	
}


CollectablesCoins::~CollectablesCoins()
{
	mRenderer = NULL;
}
