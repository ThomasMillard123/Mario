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


bool InitSDL();
bool Update();
void CloseSDL();
void Render();


int main(int argc, char* args[]) {

	if (InitSDL()) {
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_MENU);

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
			


		}
		else {
			cout << "SDL_Image could not initialise. Error:" << SDL_GetError();
			return false;
		}

		
		
		
		return true;
	}
	
}


bool Update() {
	Uint32 newTime = SDL_GetTicks();
	SDL_Event e;
	SDL_PollEvent(&e);

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;

	switch (e.type)
	{
	//closes with right mousebuttion press
	case SDL_MOUSEBUTTONDOWN:
		switch (e.button.button)
		{
		case SDL_BUTTON_MIDDLE:
		case SDL_BUTTON_LEFT:
		case SDL_BUTTON_RIGHT:
			return false;
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
		
		}
	default:
		return false;
		break;
	}

}

void Render() {
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	gameScreenManager->Render();
	
	

	SDL_RenderPresent(gRenderer);
}

//free up memory by closeing window
void CloseSDL() {
	
	
	delete gameScreenManager;
	gameScreenManager = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	Mix_CloseAudio();

	IMG_Quit();
	

}