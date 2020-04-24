#include "GameScreen.h"


GameScreen::GameScreen(SDL_Renderer* renderer) {
	mRenderer = renderer;
	mGameEnd = false;

	mSpriteSheet = new Texture2D(mRenderer);
	if (!mSpriteSheet->LoadFromFile("Images/NES - Mario Bros - General Sprites.png")) {
		std::cout << "Failed to load Sprite texture!";
	}

	mHUD = new Text(mRenderer, mSpriteSheet);
}

void GameScreen::Render() {

}


void GameScreen::Update(float deltaTime, SDL_Event e) {
	//check end game conditions 
	if (mCoinCount == mNumberOfCoins) {
		if (mLeveLHUD == "LEVEL 1 ") {
			mNextScreen = SCREEN_LEVEL2;
		}else if (mLeveLHUD == "LEVEL 2 ") {
			mNextScreen = SCREEN_GAMEOVER;
		}
		mGameEnd = true;
		mBackgroundMusic->PauseSound();
	}
	else if (mNumberOfPlayers == 2) {
		if (mPlayerOne->GetCharacterState() == DEAD && mPlayerTwo->GetCharacterState() == DEAD) {
			mNextScreen = SCREEN_GAMEOVER;
			mGameEnd = true;
			mBackgroundMusic->PauseSound();
		}
	}
	else if (mNumberOfPlayers < 2) {
		if (mPlayerOne->GetCharacterState() == DEAD) {
			mNextScreen = SCREEN_GAMEOVER;
			mGameEnd = true;
			mBackgroundMusic->PauseSound();
		}
	}
}

bool GameScreen::GetGameState() {
	return mGameEnd;
}

SCREENS GameScreen::GetNextScreen() {
	return mNextScreen;
}

int GameScreen::GetNumberOfPlayers() {
	return mNumberOfPlayers;
}
int GameScreen::GetScore() {
	return mScore;
}
GameScreen::~GameScreen() {
	mRenderer = nullptr;
}
