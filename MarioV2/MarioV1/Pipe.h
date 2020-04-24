#ifndef _PIPE_H
#define _PIPE_H

#include "Block.h"
class Pipe :
	public Block
{
public:
	Pipe(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map,FACING faceingDirection);
	~Pipe();

	void Render();

private:
	FACING mFaceingDirection;
};

#endif