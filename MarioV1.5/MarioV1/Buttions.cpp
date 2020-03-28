#include "Buttions.h"



Buttions::Buttions(SDL_Renderer* renderer,Texture2D* texture, Vector2D startPosition,Vector2D positionOnSpritesheet)
{
	mRenderer = renderer;
	mTexture = texture;
	mPosition = startPosition;
	mPosiononOnSpritesheet = positionOnSpritesheet;
}


void Buttions::Render() {
	 mButtionSpriteWidth = mTexture->GetWidth()/4;
	 mButtionSpriteHeight = mTexture->GetHeight()/31;
	 int yPos = mButtionSpriteHeight * mPosiononOnSpritesheet.y;
	 int xPos = mButtionSpriteWidth *mPosiononOnSpritesheet.x;
	 SDL_Rect portionOfSpritesheet = { xPos,yPos,mButtionSpriteWidth,mButtionSpriteHeight };
	 SDL_Rect destRect = { SCREEN_WIDTH / 2 - mButtionSpriteWidth / 2,mPosition.y,mButtionSpriteWidth,mButtionSpriteHeight };
	 mTexture->RenderSpritesheet(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
}



void Buttions::Update(float deltaTime, SDL_Event e) {
}


Rect2D Buttions::GetCollisionBox() {
	return Rect2D(mPosition.x, mPosition.y, mButtionSpriteWidth+10, mButtionSpriteHeight+20);
}

Buttions::~Buttions()
{
	
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;

}
