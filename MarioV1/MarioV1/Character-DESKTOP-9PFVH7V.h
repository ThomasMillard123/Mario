#pragma once
#include<iostream>
#include"Commons.h"
#include<SDL.h>
using namespace std;

class Texture2D;

class Character
{
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	bool mJumping;
	bool mCanJump;
	float mJumpForce;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition);
	~Character();

	virtual void render();
	virtual void update(float deltaTime, SDL_Event e);

	void setPosition(Vector2D newPosition);
	Vector2D getPosition();
	void addGravity(float deltaTime);
	void jump();

private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
};

