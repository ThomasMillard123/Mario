#ifndef _BUTTIONS_H
#define _BUTTIONS_H

#include<iostream>
#include<string>
#include"Commons.h"
#include<SDL.h>
#include"Sound.h"
#include"Texture2D.h"



class Buttions
{
public:
	Buttions(SDL_Renderer* renderer, Texture2D* texture, Vector2D startPosition, Vector2D positionOnSpritesheet);
	~Buttions();
	 void Render();
	 void Update(float deltaTime, SDL_Event e);

	//posiotion infromation
	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	//collion infromation
	Rect2D GetCollisionBox();

private:
	SDL_Renderer* mRenderer;

	//buttion infromation
	Vector2D mPosition;
	Vector2D mPosiononOnSpritesheet;
	Texture2D* mTexture;
	int mButtionSpriteWidth;
	int mButtionSpriteHeight;
};

#endif