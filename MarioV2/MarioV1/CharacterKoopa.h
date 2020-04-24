#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H
#include "Character.h"
class LevelMap;
class CharacterKoopa :
	public Character
{
protected:
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map,FACING startFaceing,float movementSpeed);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	bool GetAlive();
	void SetAlive(bool setAlive);
	bool GetInjured();
private:
	
	float mMovementSpeed;
	
	bool mAlive;
	
	bool mInjured;
	float mInjuredTime;

	void FlipRightwayUp();
	
};

#endif