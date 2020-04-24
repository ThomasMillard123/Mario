#ifndef _COLLECTABLECOINS_H
#define _COLLECTABLECOINS_H
#include "Collectables.h"
class CollectablesCoins :
	public Collectables
{
public:
	CollectablesCoins(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CollectablesCoins();


	void Render();
	void Update(float deltaTime, SDL_Event e);
	
private:
	float mRotation;
};
#endif
