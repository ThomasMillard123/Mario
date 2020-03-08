#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<iostream>
#include"Constants.h"
#include"Texture2D.h"
#include"Commons.h"
#include"GameScreenManager.h"
using namespace::std;

Uint32 gOldTime;
SDL_Window* gWindow = NULL;
GameScreenManager* gameScreenManager;
SDL_Renderer* gRenderer = NULL;
//SDL_Texture* gTexture = NULL;
Texture2D* gTexture = NULL;

bool InitSDL();
bool Update();
void CloseSDL();

void Render();
//SDL_Texture* LoadTextureFromFile(string path);
//void FreeTexture();


int main(int argc, char* args[]) {

	if (InitSDL()) {
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);

		gOldTime = SDL_GetTicks();
		bool quit= false;

		while (!quit)
		{
			Render();
			quit = Update();
		}
	}

	CloseSDL();

	return 0;
}

//creates the window
bool InitSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		cout << "SDL did not initialise.Error:" << SDL_GetError();
		return false;
	}
	else {
		gWindow = SDL_CreateWindow(
			"Mario",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HIGHT,
			SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			cout << "Window was not created.Error:" << SDL_GetError();
			return false;
		}


		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer != NULL) {
			int imageFLags = IMG_INIT_PNG;
			
			if (!(IMG_Init(imageFLags) & imageFLags)) {
				cout << "SDL_Image could not initialise. Error:" << IMG_GetError();
				return false;
			}
			/*gTexture = new Texture2D(gRenderer);
			if (!gTexture->LoadFromFile("Images/test.bmp")) {
			return false;
			}*/


		}
		else {
			cout << "SDL_Image could not initialise. Error:" << SDL_GetError();
			return false;
		}

		/*gTexture = LoadTextureFromFile("Images/test.bmp");
		if (gTexture == NULL) {
			
			return false;
		}*/
		
		return true;
	}
	
}

bool Update() {
	Uint32 newTime = SDL_GetTicks();
	SDL_Event e;
	SDL_PollEvent(&e);
	gameScreenManager->update((float)(newTime - gOldTime) / 1000.0f, e);


	switch (e.type)
	{
	//closes with right mousebuttion press
	case SDL_MOUSEBUTTONDOWN:
		switch (e.button.button)
		{
		case SDL_BUTTON_MIDDLE:
		case SDL_BUTTON_LEFT:
			return false;
			break;
		case SDL_BUTTON_RIGHT:
			return true;
			break;
		
		}

	//closes with press of x buttion at top of window
	case SDL_QUIT:
		return true;
		break;
	//closes with press of key. This case it is q.
	case SDL_KEYUP:
		switch (e.key.keysym.sym) 
		{
		case SDLK_q:
			gameScreenManager->ChangeScreen(SCREEN_LEVEL2);
			return false;
			break;
		}
	default:
		return false;
		break;
	}


	

	gOldTime = newTime;
}

void Render() {
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	gameScreenManager->render();
	
	//SDL_Rect renderLocation = { 0,0, SCREEN_WIDTH,SCREEN_HIGHT };
	//SDL_RenderCopyEx(gRenderer, gTexture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);

	SDL_RenderPresent(gRenderer);
}

//SDL_Texture* LoadTextureFromFile(string path) {
//	FreeTexture();
//	SDL_Texture* pTexture = NULL;
//
//	SDL_Surface* pSurface = IMG_Load(path.c_str());
//
//	if (pSurface != NULL) {
//		pTexture = SDL_CreateTextureFromSurface(gRenderer, pSurface);
//		
//		if (pTexture == NULL) {
//			std::cout << "Unable to create texture from surface.Error:" << SDL_GetError() << std::endl;
//
//		}
//		SDL_FreeSurface(pSurface);
//
//	}
//	else {
//		std::cout << "Unable to create texture from surface.Error:" << IMG_GetError() << std::endl;
//
//	}
//	return pTexture ;
//}
//
//void FreeTexture() {
//	if (gTexture != NULL) {
//
//		SDL_DestroyTexture(gTexture);
//		gTexture = NULL;
//		
//	}
//}

//free up memory by closeing window
void CloseSDL() {
	
	/*FreeTexture();*/
	/*delete gTexture;
	gTexture = NULL;*/

	delete gameScreenManager;
	gameScreenManager = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	IMG_Quit();

}