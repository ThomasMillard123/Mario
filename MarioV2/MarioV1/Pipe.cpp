#include "Pipe.h"
Pipe::Pipe(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING faceingDirection) :Block(renderer, imagePath, startPosition, map) {
	mFaceingDirection = faceingDirection;
}

Pipe::~Pipe() {

}

void Pipe::Render() {
	if (mFaceingDirection == FACING_RIGHT) {
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else if(mFaceingDirection==FACING_LEFT)
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
}