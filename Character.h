#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "SDL.h"
#include "Commons.h"
#include <iostream>
#include <string>
#include "LevelMap.h"

using namespace::std;

class Texture2D;

class Character {

public:

	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

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

	bool mJumping;
	bool mCanJump;
	float mJumpForce;

	virtual void Movement(float deltaTime);


private:

	bool mMovingLeft;
	bool mMovingRight;

	float velocity;
	float acceleration = 0.02f;


	LevelMap* mCurrentLevelMap;

	FACING mFacingDirection;


};
#endif //_CHARACTER_H