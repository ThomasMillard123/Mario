#include "GameScreenGameOver.h"

#include <iostream>
#include <fstream>	
#include<algorithm>

#include"Texture2D.h"
#include"Collisions.h"
#include"GameScreenManager.h"

GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer, int score) :GameScreen(renderer)
{
	mScoreInt = score;
	mSpriteSheet = new Texture2D(mRenderer);
	if (!mSpriteSheet->LoadFromFile("Images/NES - Mario Bros - General Sprites.png")) {
		std::cout << "Failed to load Sprite texture!";
	}
	mScore = new Text(mRenderer, mSpriteSheet);
	mName = new Text(mRenderer, mSpriteSheet);
	mInstruction = new Text(mRenderer, mSpriteSheet);
	mNameText = "";
}

void GameScreenGameOver::Render() {
	//game over text
	int mSingleSpriteWidth = mSpriteSheet->GetWidth() / 5;
	int mSingleSpriteHight = mSpriteSheet->GetHeight() / 31;
	int mYPosition = mSingleSpriteHight * 7;
	int mXPosition = mSingleSpriteWidth * 0.7;
	SDL_Rect portionOfSpritesheet = { mXPosition,mYPosition,mSingleSpriteWidth,mSingleSpriteHight };
	SDL_Rect destRect = { SCREEN_WIDTH / 2 - mSingleSpriteWidth / 2,0,mSingleSpriteWidth,mSingleSpriteHight };
	mSpriteSheet->RenderSpritesheet(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	
	std::string scoreText = to_string(mScoreInt);
	
	mScore->Render("Score "+ scoreText, Vector2D(221, 20));
	mInstruction->Render("Enter Name", Vector2D(176, 50));
	mName->Render(mNameText, Vector2D(221, 70));
	mInstruction->Render("Press space to continue", Vector2D(176, 100));
	
}



void GameScreenGameOver::Update(float deltaTime, SDL_Event e) {
	mName->EnterText(mNameText, e);
	switch (e.type)
	{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_SPACE:
				UpdateHightScores();
				mGameEnd = true;
				mNextScreen = SCREEN_HIGHSCORES;
			}
	}
}

void GameScreenGameOver::UpdateHightScores() {
	std::ifstream scoreBoradOutput;
	string TextFile = "";
	std::string lineOfText;

	int scores[10];
	int scoresOrder[10];
	//creat files
	std::ofstream start("HighScores.txt", std::ios::in | std::ios::app);
	// Close the file
	start.close();

	scoreBoradOutput.open("HighScores.txt");
	if (scoreBoradOutput.is_open())
	{
		int pos;
		int smallestNum;
		int i = 0;
		int scoreHold = mScoreInt;
		std::string numbersInText;
		std::string currenttextLine;
		std::string outputText = "";

		//loop each line
		while (getline(scoreBoradOutput, lineOfText))
		{
			numbersInText = lineOfText;
			currenttextLine = lineOfText;

			// find the numbers within each line
			pos = numbersInText.find(" ");
			numbersInText.replace(0, pos, "");
			scores[i] = std::stoi(numbersInText);
			scoresOrder[i] = std::stoi(numbersInText);
			std::sort(std::begin(scoresOrder), std::end(scoresOrder), std::greater<int>());

			if (mScoreInt >= scores[i]) {
				if (i == 9) {

					outputText += mNameText + " " + std::to_string(mScoreInt) + "\n";
					mScoreInt = -1;
				}
				else
				{
					outputText += mNameText + " " + std::to_string(mScoreInt) + "\n";
					outputText += currenttextLine + "\n";
					mScoreInt = -1;
				}
			}
			else if (mScoreInt <= scores[i] && scores[i] > scoresOrder[9]) {
				outputText += currenttextLine + "\n";
			}
			else if (scores[i] == scoresOrder[9]) {

				if (scores[i] <= scoreHold) {
					//don't add text
				}
				else if (scores[i] > mScoreInt) {
					outputText += currenttextLine + "\n";
					mScoreInt = -1;

				}

			}

			i++;
		}

		if (mScoreInt == -1) {
			//don't add text

		}
		//add inputed text if there lest than 11 lines of text
		else if (i < 11 && mScoreInt>0) {
			outputText += mNameText + " " + std::to_string(mScoreInt) + "\n";

		}
		TextFile += outputText;
	}
		// Close the file.
		scoreBoradOutput.close();

		std::ofstream scoreBoradInput("HighScores.txt", std::ios::in | std::ios::trunc);
		if (!scoreBoradInput)
		{
			std::cout << "File could not be opened! \n";
			system("pause");

		}
		//output to file
		scoreBoradInput << TextFile;

		scoreBoradInput.close();
	
}

GameScreenGameOver::~GameScreenGameOver()
{
	delete mSpriteSheet;
	mSpriteSheet = NULL;

	delete mInstruction;
	mInstruction = NULL;

	delete mScore;
	mScore = NULL;
}
