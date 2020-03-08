#include"GameScreenLevel1.h"
#include<iostream>

#include"Texture2D.h"
#include"Collisions.h"
#include"PowBlock.h"
#include"CharacterMario.h"
#include"CharacterLuigi.h"
#include"CharacterKoopa.h";
#include"SoundMusic.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	mLevelMap = NULL;

	SetUpLevel();
}

bool GameScreenLevel1::SetUpLevel() {

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		std::cout << "Failed to load background texture!";
		return false;

	}
	SetLevelMap();

	mBackgroundMusic = new SoundMusic();
	mBackgroundMusic->LoadSound("Music/Mario.mp3");
	mBackgroundMusic->PlaySound();
	mPlayerOne = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(4, 320),mLevelMap);
	mPlayerTwo = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(40, 320),mLevelMap);
	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	mScreenshake = false;
	mBackgroundYPos = 0.0f;
}
void GameScreenLevel1::SetLevelMap() {
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
		{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};
	if (mLevelMap != NULL) {
		delete mLevelMap;
	}
	mLevelMap = new LevelMap(map);
	
}



void GameScreenLevel1::Render() {
	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->Render();
	}
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	mPlayerOne->Render();
	mPlayerTwo->Render();
	mPowBlock->Render();
}



void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
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
	mPlayerTwo->Update(deltaTime, e);
	if (Collisions::Instance()->Box(mPlayerOne->GetCollisionBox(), mPlayerTwo->GetCollisionBox())) {
		
	}
	UpdateEnemies(deltaTime, e);
	UpdatePowBlock();
	
}

void GameScreenLevel1::UpdatePowBlock() {
	if (Collisions::Instance()->Box(mPlayerOne->GetCollisionBox(),mPowBlock->GetCollisionBox())) {
		if (mPowBlock->IsAvailable()) {
			if (mPlayerOne->IsJumping()) {
				cout << "Hit";
				DoScreenshake();
				mPowBlock->TakeAHit();
				mPlayerOne->CancelJump();
			}
		}
	}

	if (Collisions::Instance()->Box(mPlayerTwo->GetCollisionBox(),mPowBlock->GetCollisionBox())) {
		if (mPowBlock->IsAvailable()) {
			if (mPlayerTwo->IsJumping()) {
				DoScreenshake();
				mPowBlock->TakeAHit();
				mPlayerTwo->CancelJump();
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

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed) {
	CharacterKoopa* KoopaCharacter; 
	KoopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", position, mLevelMap, direction, speed);
	mEnemies.push_back(KoopaCharacter);
}

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
					/*mPlayerOne->setState(CHARACTERSTATE_PLAYER_DEATH);*/
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


GameScreenLevel1::~GameScreenLevel1()  {

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mPlayerOne;
	mPlayerOne = NULL;
	delete mPlayerTwo;
	mPlayerTwo = NULL;
	delete mPowBlock;
	mPowBlock = NULL;

	mEnemies.clear();
}
