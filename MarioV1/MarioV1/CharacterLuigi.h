#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H


#include"Character.h"
class CharacterLuigi:public Character
{

protected:
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	


private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMoveingRight;
	float mCollisionRadius;
	LevelMap* mCurrentLevelMap;
};

#endif
