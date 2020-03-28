#ifndef _BLOCKS_H
#define _BLOCKS_H

#include<iostream>
#include<SDL.h>
#include<string>
#include"Commons.h"
#include"Texture2D.h"
#include "Constants.h"
#include"LevelMap.h"
#include"SoundEffect.h"
class Block
{
public:
	Block(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Block();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void Shake(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();
	Rect2D GetCollisionBox();

	
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

private:
	LevelMap* mCurrentLevelMap;
	float mCollisionRadius;
};

#endif