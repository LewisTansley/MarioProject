#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) {

    mRenderer = renderer;

    mPosition = startPosition;

    mCurrentLevelMap = map;

    mCollisionRadius = 15.0f;

}

Character::~Character() {}

void Character::Update(float deltaTime, SDL_Event e) {}

void Character::Render() {}

void Character::Movement(float deltaTime) {

    if (mMovingLeft) {

        if (velocity < 0.5f) {
            velocity += acceleration * (deltaTime / 16);
        }

        mPosition.x -= velocity * deltaTime;
    }

    if (mMovingRight) {

        if (velocity < 0.5f) {
            velocity += acceleration * (deltaTime / 16);
        }

        mPosition.x += velocity * deltaTime;
    }

    SetPosition(mPosition);

}

void Character::SetPosition(Vector2D newPosition) {

    mPosition = newPosition;

}

Vector2D Character::GetPosition() {

    return mPosition;

}

float Character::GetCollisionRadius() {
    return mCollisionRadius;
}