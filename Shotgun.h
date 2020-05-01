#pragma once
#ifndef _SHOTGUN_H
#define _SHOTGUN_H

#include "SDL.h"
#include <iostream>
#include <string>
#include "LevelMap.h"
#include "Character.h"
#include "SoundEffect.h"

using namespace::std;

class Texture2D;

class Shotgun : public Character {

public:

	Shotgun(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed, int tiles);
	~Shotgun();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();


protected:

	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	float mCollisionRadius;

	bool mColliding;
	bool mCollidingBottom;
	bool mCollidingTop;
	bool mCollidingLeft;
	bool mCollidingRight;

	int GetSpriteCount;

private:

	bool mMovingLeft;
	bool mMovingRight;

	float mSingleSpriteWidth;
	float mSingeSpriteHeight;


	bool mInjured;

	float mInjuredTime;

	LevelMap* mCurrentLevelMap;

	FACING mFacingDirection;

	float mMovementSpeed;
	float velocity;
	float acceleration = 0.005f;

};
#endif //_SHOTGUN_H