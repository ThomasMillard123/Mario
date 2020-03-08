#include "GameScreenManager.h"
#include"GameScreen.h"
#include"GameScreenLevel1.h"
#include"GameScreenLevel2.h"


GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {
	mRenderer = renderer;
	mCurrentScreen= NULL;

	ChangeScreen(startScreen);

}


void GameScreenManager::Render() {
	mCurrentScreen->Render();
}


void GameScreenManager::Update(float deltaTime, SDL_Event e) {
	mCurrentScreen->Update(deltaTime, e);
}



void GameScreenManager::ChangeScreen(SCREENS newScreen) {
	if (mCurrentScreen != NULL) {
		delete mCurrentScreen;
	}
	GameScreenLevel1* tempScreen;
	GameScreenLevel2* tempScreen1;

	switch (newScreen)
	{
	case SCREEN_INTRO:
		break;
	case SCREEN_MENU:
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_LEVEL2:
		tempScreen1 = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen1;
		tempScreen1 = NULL;
		break;
	case SCREEN_GAMEOVER:
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}
}


GameScreenManager::~GameScreenManager() {

	mRenderer = NULL;

	delete mCurrentScreen;
	mCurrentScreen = NULL;

}