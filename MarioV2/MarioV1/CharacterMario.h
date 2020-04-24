#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

 #include"Character.h"
#include"Sound.h"
class LevelMap;

class CharacterMario: public Character
{
protected:
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);

	~CharacterMario();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	
	


};

#endif