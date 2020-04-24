#ifndef _TEXT_H
#define _TEXT_H
#include<iostream>
#include<string>

#include"Texture2D.h"
#include"Commons.h"

class Text
{
public:
	Text(SDL_Renderer* renderer, Texture2D* texture);
	~Text();

	void Update();
	void Render(std::string text,Vector2D position);
	void EnterText(std::string &Text, SDL_Event e);
private:
	std::string mText;
	Texture2D* mTexture;
	Vector2D mPosition;

	SDL_Renderer* mRenderer;

	int mSingleSpriteWidth, mSingleSpriteHight,mYPosition,mXPosition;
	SDL_Rect mPortionOfSpritesheet;
	SDL_Rect mDestRect;
};

#endif