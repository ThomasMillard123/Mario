#ifndef _COLLECTABLES_H
#define _COLLECTABLES_H

#include<iostream>
#include<SDL.h>
#include<string>
#include"Commons.h"
#include"Texture2D.h"
#include "Constants.h"
#include"LevelMap.h"
#include"SoundEffect.h"
class Collectables
{
public:
	Collectables(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Collectables();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();
	Rect2D GetCollisionBox();

	bool GetState();
	void SetState(bool setState);
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	bool mState;
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

private:
	LevelMap* mCurrentLevelMap;
	float mCollisionRadius;
};

#endif
