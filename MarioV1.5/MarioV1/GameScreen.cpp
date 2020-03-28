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
