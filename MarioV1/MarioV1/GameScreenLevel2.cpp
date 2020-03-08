#include"GameScreenLevel2.h"
#include<iostream>
#include"Texture2D.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
}


bool GameScreenLevel2::SetUpLevel() {

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		std::cout << "Failed to load background texture!";
		return false;

	}


}


void GameScreenLevel2::Render() {
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}


void GameScreenLevel2::Update(float deltaTime, SDL_Event e) {

}

GameScreenLevel2::~GameScreenLevel2() {

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}