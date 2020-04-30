#include "Collisions.h"
#include "Character.h"

Collisions* Collisions::mInstance = NULL;

Collisions::Collisions() {

}
Collisions::~Collisions() {
	mInstance = NULL;
}
Collisions* Collisions::Instance() {

	if (!mInstance) {
		mInstance = new Collisions;
	}

	return mInstance;

}
bool Circle(Character* character1, Character* character2) {

	float xDistance = character1->GetPosition().x - character2->GetPosition().x;
	float yDistance = character1->GetPosition().y - character2->GetPosition().y;
	
	float xyDistance = sqrt(xDistance * xDistance + yDistance * yDistance);

	double combinedDistance = (character1->GetCollisionRadius() + character2->GetCollisionRadius());

	return xyDistance < combinedDistance;

}

