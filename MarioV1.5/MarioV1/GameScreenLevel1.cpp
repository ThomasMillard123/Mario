#include"GameScreenLevel1.h"
#include<iostream>
#include<fstream>

#include"Texture2D.h"
#include"Collisions.h"
#include"PowBlock.h"
#include"CharacterMario.h"
#include"CharacterLuigi.h"
#include"CharacterKoopa.h";
#include"CollectablesCoins.h"
#include"SoundMusic.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer, int numberOfPlayers,int score) : GameScreen(renderer) {
	SetUpSounds();
	mLevelMap = NULL;
	mScore = score;
	mNumberOfPlayers = numberOfPlayers;
	mLeveLHUD = "LEVEL 1 ";
	SetUpLevel();
	
}
//setups
bool GameScreenLevel1::SetUpLevel() {
	mCoinCount = 0;
	
	Layer0 = new Texture2D(mRenderer);
	if (!Layer0->LoadFromFile("Images/mario-background-png.png")) {
		std::cout << "Failed to load background texture!";
		return false;

	}
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		std::cout << "Failed to load background texture!";
		return false;

	}
	SetLevelMap();



	mPlayerOne = new CharacterMario(mRenderer, "Images/mario_Sprite.png", Vector2D(0, 320),mLevelMap);
	if (mNumberOfPlayers == 2) {
		mPlayerTwo = new CharacterLuigi(mRenderer, "Images/luigi_sprite.png", Vector2D(600, 320), mLevelMap);
	}
	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	CreateKoopa(Vector2D(0, 0), FACING_LEFT, KOOPA_SPEED);
	CreateKoopa(Vector2D(SCREEN_WIDTH-50, 0), FACING_RIGHT, KOOPA_SPEED);
	
	mScreenshake = false;
	mBackgroundYPos = 0.0f;
}
void GameScreenLevel1::SetLevelMap() {
	int map[MAP_HEIGHT][MAP_WIDTH];

	std::fstream input;
	input.open("Levels/Level1.txt");
	if (!input.good()) {
		cerr << "File not open" << endl;
	}
	string line;
	string no;
	for (int y = 0; y < MAP_HEIGHT; y++) {
		input >> line;

		for (int x = 0; x < MAP_WIDTH; x++) {
			no = line[x];
			map[y][x] = stoi(no);
			if (map[y][x] == 3) {
				CreateCoin(Vector2D(32*x, 32*y));
			}
		}
	}

	input.close();


	if (mLevelMap != NULL) {
		delete mLevelMap;
	}
	mLevelMap = new LevelMap(map);
	
}

void GameScreenLevel1::SetUpSounds() {
	mBackgroundMusic = new SoundMusic();
	mBackgroundMusic->LoadSound("Music/Mario.mp3");

	mNewLevel = new SoundEffect();
	mNewLevel->LoadSound("SoundEffects/Resspwan.wav");
	mNewLevel->PlaySound();
	mBackgroundMusic->PlaySound();

	mCoinCollect = new SoundEffect();
	mCoinCollect->LoadSound("SoundEffects/coin_Collect.wav");
}
//creat objects
void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed) {
	CharacterKoopa* KoopaCharacter; 
	KoopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", position, mLevelMap, direction, speed);
	mEnemies.push_back(KoopaCharacter);
}
void GameScreenLevel1::CreateCoin(Vector2D position) {
	CollectablesCoins* coin;
	coin = new CollectablesCoins(mRenderer, "Images/Coin.png", position, mLevelMap);
	mCoins.push_back(coin);
}

//update objects
void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	
	//check end game conditions 
	if (mCoinCount == 10) {
		mNextScreen = SCREEN_LEVEL2;
		mGameEnd = true;
		mBackgroundMusic->PauseSound();
	}
	else if (mNumberOfPlayers==2) {
		if (mPlayerOne->GetCharacterState() == DEAD && mPlayerTwo->GetCharacterState()==DEAD) {
			mNextScreen = SCREEN_GAMEOVER;
			mGameEnd = true;
			mBackgroundMusic->PauseSound();
		}
	}
	else if(mNumberOfPlayers<2){
		if (mPlayerOne->GetCharacterState() == DEAD) {
			mNextScreen = SCREEN_GAMEOVER;
			mGameEnd = true;
			mBackgroundMusic->PauseSound();
		}
	}

	if (mScreenshake) {
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		if (mScreenshakeTime <= 0.0f) {
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	mPlayerOne->Update(deltaTime, e);
	if (mNumberOfPlayers == 2) {
		mPlayerTwo->Update(deltaTime, e);
	}
	
	UpdateEnemies(deltaTime, e);
	UpdatePowBlock();
	UpdateCoin(deltaTime, e);
}

//coins
void GameScreenLevel1::UpdateCoin(float deltaTime, SDL_Event e) {
	
	int coinIndexToDelete = -1;
	for (unsigned int i = 0; i < mCoins.size(); i++) {
		mCoins[i]->Update(deltaTime, e);
		if (Collisions::Instance()->Box(mPlayerOne->GetCollisionBox(), mCoins[i]->GetCollisionBox())) {
			mCoinCollect->PlaySound();
			mCoins[i]->SetState(false);
			mScore += 50;
			mCoinCount++;
			if (!mCoins[i]->GetState()) {
			coinIndexToDelete = i;
			}

		}
		if (mNumberOfPlayers == 2) {
			if (Collisions::Instance()->Box(mPlayerTwo->GetCollisionBox(), mCoins[i]->GetCollisionBox())) {
				mCoinCollect->PlaySound();
				mCoins[i]->SetState(false);
				mScore += 50;
				mCoinCount++;
				if (!mCoins[i]->GetState()) {
					coinIndexToDelete = i;
				}

			}
		}
	}	
	if (coinIndexToDelete != -1) {
		mCoins.erase(mCoins.begin()+ coinIndexToDelete);	
	}
}

//powblocck
void GameScreenLevel1::UpdatePowBlock() {
	if (mNumberOfPlayers == 1) {
		if (Collisions::Instance()->Box(mPlayerOne->GetCollisionBox(), mPowBlock->GetCollisionBox())) {
			if (mPowBlock->IsAvailable()) {
				if (mPlayerOne->IsJumping()) {
					DoScreenshake();
					mPowBlock->TakeAHit();
					mPlayerOne->CancelJump();
				}
			}
		}
	}
	else if (mNumberOfPlayers == 2) {
		if (Collisions::Instance()->Box(mPlayerOne->GetCollisionBox(), mPowBlock->GetCollisionBox())) {
			if (mPowBlock->IsAvailable()) {
				if (mPlayerOne->IsJumping()) {
					DoScreenshake();
					mPowBlock->TakeAHit();
					mPlayerOne->CancelJump();
				}
			}
		}
		if (Collisions::Instance()->Box(mPlayerTwo->GetCollisionBox(), mPowBlock->GetCollisionBox())) {
			if (mPowBlock->IsAvailable()) {
				if (mPlayerTwo->IsJumping()) {
					DoScreenshake();
					mPowBlock->TakeAHit();
					mPlayerTwo->CancelJump();
				}
			}
		}
	}
}

void GameScreenLevel1::DoScreenshake() {
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
	for (unsigned int i = 0; i < mEnemies.size(); i++) {

		mEnemies[i]->TakeDamage();
	}

}

//enemies
void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e) {
	if (!mEnemies.empty()) {
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++){

			if (mEnemies[i]->GetPosition().y > 300.0f) {
				if (mEnemies[i]->GetPosition().x<(float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || mEnemies[i]->GetPosition().x
				>SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f)) {
					mEnemies[i]->SetAlive(false);
				}
			}
			mEnemies[i]->Update(deltaTime, e);

			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f)
				&& (mEnemies[i]->GetPosition().x<64.0f || mEnemies[i]->GetPosition().x>SCREEN_WIDTH - 96.0f)) {

			}
			else {
				if (Collisions::Instance()->Circle(mEnemies[i], mPlayerOne)) {
					mPlayerOne->SetCharacterState(DEAD);
					
				}
				if (mNumberOfPlayers == 2) {
					if (Collisions::Instance()->Circle(mEnemies[i], mPlayerTwo)) {
						mPlayerTwo->SetCharacterState(DEAD);

					}
				}
			}

			if (!mEnemies[i]->GetAlive()) {
				enemyIndexToDelete = i;
			}

		}
		if (enemyIndexToDelete != -1) {
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}


//render objects
void GameScreenLevel1::Render() {
	Layer0->Render(Vector2D(), SDL_FLIP_NONE);
	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->Render();
	}
	for (unsigned int i = 0; i < mCoins.size(); i++) {
		mCoins[i]->Render();
	}
	
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	mPlayerOne->Render();
	if (mNumberOfPlayers == 2) {
		mPlayerTwo->Render();
	}
	mPowBlock->Render();


	std::string scoreText = to_string(mScore);
	mHUD->Render(mLeveLHUD +" Score " + scoreText, Vector2D(0, SCREEN_HIGHT-20));
	
}

GameScreenLevel1::~GameScreenLevel1()  {
	//clean up textures
	delete Layer0;
	Layer0 = NULL;
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	//celan up characters
	delete mPlayerOne;
	mPlayerOne = NULL;
	delete mPlayerTwo;
	mPlayerTwo = NULL;

	mEnemies.clear();
	
	//clean up collectables
	mCoins.clear();
	delete mPowBlock;
	mPowBlock = NULL;

	//clean up sound
	delete mBackgroundMusic;
	mBackgroundMusic = NULL;
	delete mNewLevel;
	mNewLevel = NULL;
	delete mCoinCollect;
	mCoinCollect = NULL;

	//clean up level map
	delete mLevelMap;
	mLevelMap = NULL;
	
}
