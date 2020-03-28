#include "GameScreenManager.h"
#include"GameScreen.h"
#include"GameScreenMenu.h"
#include"GameScreenLevel1.h"
#include"GameScreenLevel2.h"
#include"GameScreenGameOver.h"
#include"GameScreenHighScores.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {
	mRenderer = renderer;
	mCurrentScreen= NULL;
	mNumberOfPlayers = 0;
	ChangeScreen(startScreen);

}


void GameScreenManager::Render() {
	mCurrentScreen->Render();
}


void GameScreenManager::Update(float deltaTime, SDL_Event e) {
	
	mCurrentScreen->Update(deltaTime, e);
	if (mCurrentScreen->GetGameState()) {
		mScore = mCurrentScreen->GetScore();
		mNumberOfPlayers = mCurrentScreen->GetNumberOfPlayers();
		ChangeScreen(mCurrentScreen->GetNextScreen());
	}
}



void GameScreenManager::ChangeScreen(SCREENS newScreen) {
	if (mCurrentScreen != NULL) {
		delete mCurrentScreen;
	}
	GameScreenMenu* tempScreen;
	GameScreenLevel1* tempScreen1;
	GameScreenLevel2* tempScreen2;
	GameScreenGameOver* tempScreen3;
	GameScreenHighScores* tempScreen4;
	switch (newScreen)
	{
	case SCREEN_INTRO:
		break;
	case SCREEN_MENU:
		tempScreen = new GameScreenMenu(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_LEVEL1:
		tempScreen1 = new GameScreenLevel1(mRenderer,mNumberOfPlayers,mScore);
		mCurrentScreen = (GameScreen*)tempScreen1;
		tempScreen1 = NULL;
		break;
	case SCREEN_LEVEL2:
		tempScreen2 = new GameScreenLevel2(mRenderer, mNumberOfPlayers, mScore);
		mCurrentScreen = (GameScreen*)tempScreen2;
		tempScreen2 = NULL;
		break;
	case SCREEN_GAMEOVER:
		tempScreen3 = new GameScreenGameOver(mRenderer,mScore);
		mCurrentScreen = (GameScreen*)tempScreen3;
		tempScreen3 = NULL;
		break;
	case SCREEN_HIGHSCORES:		
		tempScreen4 = new GameScreenHighScores(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen4;
		tempScreen4 = NULL;
		
		break;
	default:
		break;
	}
}
//TODO: HIGHSCORES screen

GameScreenManager::~GameScreenManager() {

	mRenderer = NULL;

	delete mCurrentScreen;
	mCurrentScreen = NULL;

}