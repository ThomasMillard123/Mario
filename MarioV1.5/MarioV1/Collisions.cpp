#include "Collisions.h"

#include"CharacterMario.h"
#include"CharacterLuigi.h"
#include"Character.h"


Collisions* Collisions::mInstance = NULL;

Collisions::Collisions()
{


}

Collisions* Collisions::Instance() {
	if (!mInstance)
	{
		mInstance = new Collisions;
	}
	return mInstance;
}
bool Collisions::Circle(Character* character1, Character* character2) {
	Vector2D vec = Vector2D((character1->GetPosition().x - character2->GetPosition().x), 
							(character1->GetPosition().y - character2->GetPosition().y));
	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	double combineDistance = (character1->GetCollisionRadius() + character2->GetCollisionRadius());
	return distance < combineDistance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2) {
	//overlap collison
	/*if (rect1.x + (rect1.width / 2) > rect2.x&&
		rect1.x + (rect1.width / 2) < rect2.x + rect2.width &&
		rect1.y + (rect1.height / 2) > rect2.y&&
		rect1.y + (rect1.height / 2) < rect2.y + rect2.height) {

		return true;
	}*/

	//sides collisions
	int bottom1 = rect1.y + rect1.height;
	int bottom2 = rect2.y + rect2.height;

	int left1 = rect1.x;
	int left2 = rect2.x;

	int right1 = rect1.x+rect1.width;
	int right2 = rect2.x + rect2.width;

	int top1 = rect1.y;
	int top2 = rect2.y;

	if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2))
	{
		return true;
	}
	return false;

}

Collisions::~Collisions()
{

	mInstance = NULL;
}
