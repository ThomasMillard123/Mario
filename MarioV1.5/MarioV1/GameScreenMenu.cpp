#include "GameScreenMenu.h"

#include"Texture2D.h"
#include"Collisions.h"
#include"GameScreenManager.h"

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer):GameScreen(renderer)
{
	mScore = 0;
	mTitleTexture = new Texture2D(mRenderer);
	if (!mTitleTexture->LoadFromFile("Images/NES - Mario Bros - General Sprites.png")) {
		std::cout << "Failed to load background texture!";
	
	}
	mHighScorePos = Vector2D(SCREEN_WIDTH / 2-30, 180);
	m1PlayerPlay= new Buttions(mRenderer,mTitleTexture, Vector2D(SCREEN_WIDTH / 2, 100), Vector2D(0.6f, 4.7f));
	m2PlayerPlay = new Buttions(mRenderer, mTitleTexture, Vector2D(SCREEN_WIDTH / 2, 130),Vector2D(0.6f,5.5f));
	mHighScore = new Text(mRenderer, mTitleTexture);
}

void GameScreenMenu::Render() {
	
	int mTitleSpriteWidth = mTitleTexture->GetWidth()/1.9;
	int mTitleSpriteHeight = mTitleTexture->GetHeight()/7;
	SDL_Rect portionOfSpritesheet = { 0,0,mTitleSpriteWidth,mTitleSpriteHeight };
	SDL_Rect destRect = { SCREEN_WIDTH/2- mTitleSpriteWidth/2,0,mTitleSpriteWidth,mTitleSpriteHeight };
	mTitleTexture->RenderSpritesheet(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	
	//render buttions
	m1PlayerPlay->Render();
	m2PlayerPlay->Render();
	mHighScore->Render("highScores", mHighScorePos);
}



void GameScreenMenu::Update(float deltaTime, SDL_Event e) {
	int x;
	int y;
	//get x and y of mouse
	SDL_GetMouseState(&x, &y);
	
	cout << x <<" "<< y << endl;
	system("CLS");
	Rect2D Mouce = Rect2D(x,y, 50, 10);

	//check mouce colisions
	if (Collisions::Instance()->Box(Mouce, m1PlayerPlay->GetCollisionBox())) {
		switch (e.type)
		{
			//closes with right mousebuttion press
		case SDL_MOUSEBUTTONDOWN:
			switch (e.button.button)
			{
			case SDL_BUTTON_MIDDLE:
				break;
			case SDL_BUTTON_LEFT:
			case SDL_BUTTON_RIGHT:
				cout << "Loading 1 Player Game" << endl;
				mGameEnd = true;
				mNextScreen = SCREEN_LEVEL1;
				mNumberOfPlayers = 1;
				break;
			}
		}
	}
	if (Collisions::Instance()->Box(Mouce,m2PlayerPlay->GetCollisionBox())) {
		switch (e.type)
		{
			//closes with right mousebuttion press
		case SDL_MOUSEBUTTONDOWN:
			switch (e.button.button)
			{
			case SDL_BUTTON_MIDDLE:
				break;
			case SDL_BUTTON_LEFT:
			case SDL_BUTTON_RIGHT:
				cout << "Loading 2 Player Game"<<endl;
				mGameEnd = true;
				mNextScreen = SCREEN_LEVEL1;
				mNumberOfPlayers = 2;
				break;

			}
		}
	}
	Rect2D HighScore = Rect2D(mHighScorePos.x, mHighScorePos.y, 109, 21);
	if (Collisions::Instance()->Box(Mouce, HighScore)) {
		switch (e.type)
		{
			//closes with right mousebuttion press
		case SDL_MOUSEBUTTONDOWN:
			switch (e.button.button)
			{
			case SDL_BUTTON_MIDDLE:
				break;
			case SDL_BUTTON_LEFT:
			case SDL_BUTTON_RIGHT:
				cout << "Loading HighScores" << endl;
				mGameEnd = true;
				mNextScreen = SCREEN_HIGHSCORES;
				mNumberOfPlayers = 2;
				break;

			}
		}
	}
}


GameScreenMenu::~GameScreenMenu()
{
	delete mTitleTexture;
	mTitleTexture = NULL;
	delete m1PlayerPlay;
	m1PlayerPlay = NULL;
	delete m2PlayerPlay;
	m2PlayerPlay = NULL;
}
