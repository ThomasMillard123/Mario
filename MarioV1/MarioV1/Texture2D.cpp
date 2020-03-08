#include "Texture2D.h"

#include<SDL_image.h>
#include<iostream>
#include "Commons.h"

using namespace std;


Texture2D::Texture2D(SDL_Renderer* renderer){
	
	
	mWidth = 512;
	mHeight = 416;
	mTexture = NULL;
	mRenderer = renderer;

}


void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle) {
	
	//where to render
	SDL_Rect renderLocation = { newPosition.x,newPosition.y,Texture2D::GetWidth(),Texture2D::GetHeight() };
	//render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);
	
}

void Texture2D::RenderSpritesheet(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle ) {

	
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect,&destRect, angle, NULL, flip);

}

bool Texture2D::LoadFromFile(string path )  {
	Free();
	
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));

	mWidth = pSurface->w;
	mHeight = pSurface->h;

	if (pSurface != NULL) {
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		

		if (mTexture == NULL) {
			cout << "Unable to create texture from surface.Error:" << SDL_GetError() << endl;

		}
		SDL_FreeSurface(pSurface);

	}
	else {
		cout << "Unable to create texture from surface.Error:" << IMG_GetError() << endl;

	}
	return mTexture != NULL;
}


void Texture2D::Free() {

	if (mTexture != NULL) {

		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

Texture2D::~Texture2D(){

	Free();
	mRenderer = NULL;
}
