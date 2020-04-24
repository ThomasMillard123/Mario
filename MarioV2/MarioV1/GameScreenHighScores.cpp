#include "GameScreenHighScores.h"
#include<iostream>
#include<fstream>

GameScreenHighScores::GameScreenHighScores(SDL_Renderer* renderer):GameScreen(renderer){

	mSpriteSheet = new Texture2D(mRenderer);
	if (!mSpriteSheet->LoadFromFile("Images/NES - Mario Bros - General Sprites.png")) {
		std::cout << "Failed to load Sprite texture!";
	}
	mScore = new Text(mRenderer, mSpriteSheet);
	mInstruction = new Text(mRenderer, mSpriteSheet);
}


void GameScreenHighScores::Render() {
	mScore->Render("High Scores", Vector2D(SCREEN_WIDTH / 2-30, 0));
	OutputHightScores();
	mScore->Render("Press space to continue", Vector2D(176, 330));
}
void GameScreenHighScores::Update(float deltaTime, SDL_Event e) {
	

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			mGameEnd = true;
			mNextScreen = SCREEN_MENU;
		}
	}
}
void GameScreenHighScores::OutputHightScores() {
	
	std::ifstream scoreBoradOutput;
	scoreBoradOutput.open("HighScores.txt");

	if (scoreBoradOutput.is_open())
	{
		std::string lineOfText;

		int i = 1;
		int y = 30;
		// Loop through the entire file and output each line to the console.
		while (getline(scoreBoradOutput, lineOfText))
		{
			mScore->Render(std::to_string(i) + " " + lineOfText, Vector2D(SCREEN_WIDTH/2-30, y));
			i++;
			y += 30;
		}

		// Close the file.
		scoreBoradOutput.close();

	}
	else
	{
		// File did not open. Inform the user.
		std::cout << "Unable to open file" << std::endl;
	}
}


GameScreenHighScores::~GameScreenHighScores() {

}