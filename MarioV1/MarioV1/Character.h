#ifndef _CHARACTER_H
#define _CHARACTER_H

#include<iostream>
#include"Commons.h"
#include<SDL.h>
#include"Sound.h"
using namespace std;

class Texture2D;
class LevelMap;
class Character
{
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	bool mJumping;
	bool mCanJump;
	float mJumpForce;


	Sound* mJumpSound;
	
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);


	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();

	Rect2D GetCollisionBox();
	


	void AddGravity(float deltaTime);
	void Jump();
	bool IsJumping();
	void CancelJump();
private:
	LevelMap* mCurrentLevelMap;
	float mCollisionRadius;

};

#endif