#include "Texture2D.h"
#include<SDL_image.h>
#include<iostream>


using namespace::std;


Texture2D::Texture2D(SDL_Renderer* renderer)
{
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;

	mRenderer= NULL;
	mTexture = NULL;

	 mWidth= 0;
	 mHeight= 0;
}


void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle = 0.0f) {
	
	SDL_Rect renderLocation = { 0,0, mWidth,mHeight };
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);
	
}

bool Texture2D::LoadFromFile(string path) {
	
	SDL_Texture* mTexture= NULL;

	SDL_Surface* pSurface = IMG_Load(path.c_str());

	
	
	if (pSurface != NULL) {
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
		mWidth = pSurface->w;
		mHeight = pSurface->h;


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


Texture2D::~Texture2D()
{

	Free();
	mRenderer = NULL;
}
