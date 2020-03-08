#include "PowBlock.h"

#include<iostream>
#include<string>
#include"Texture2D.h"
#include"LevelMap.h"



PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	std::string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str())) {
		std::cout << "Faild to load texture: " << imagePath << std::endl;
	}

	mLevelMap = map;
	mSingleSpriteWidth = mTexture->GetWidth()/3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260);
}

void PowBlock::TakeAHit() {
	mNumberOfHitsLeft-=1;
	if (mNumberOfHitsLeft <= 0) {
		mNumberOfHitsLeft = 0;
		mLevelMap->ChangeTileAt(8, 7, 0);
		mLevelMap->ChangeTileAt(8, 8, 0);
	}

}

void PowBlock::Render() {
	if (mNumberOfHitsLeft > 0) {
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);
		SDL_Rect portionOfSpritesheet = { left,0,mSingleSpriteWidth,mSingleSpriteHeight };
		SDL_Rect destRect = { (int)(mPosition.x),(int)(mPosition.y),mSingleSpriteWidth,mSingleSpriteHeight };
		mTexture->RenderSpritesheet(portionOfSpritesheet, destRect, SDL_FLIP_NONE);

	}
}
Rect2D PowBlock::GetCollisionBox() {
	return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight);

}

bool PowBlock::IsAvailable() {

	return mNumberOfHitsLeft > 0;
}

PowBlock::~PowBlock()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLevelMap = NULL;
}
