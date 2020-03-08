#include"GameScreenLevel1.h"
#include<iostream>
#include"Texture2D.h"
#include"Character.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	setUpLevel();
}

bool GameScreenLevel1::setUpLevel() {

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Test.bmp")) {
		std::cout << "Failed to load background texture!";
		return false;

	}
	myCharacter = new Character(mRenderer, "Images/Mario.png", Vector2D(64, 330));

}


void GameScreenLevel1::render() {

	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	myCharacter->render();
}



void GameScreenLevel1::update(float deltaTime, SDL_Event e) {
	myCharacter->update(deltaTime, e);
}

GameScreenLevel1::~GameScreenLevel1()  {

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete myCharacter;
	myCharacter = NULL;
}
