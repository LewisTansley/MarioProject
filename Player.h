#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "SDL.h"
#include "Commons.h"
#include <iostream>
#include <string>

using namespace::std;

class Texture2D;

class Player {

public:

	Player(SDL_Renderer* renderer, string imagePath, Vector2D startPosition);
	~Player();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

protected:

	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	bool mJumping;
	bool mCanJump;
	float mJumpForce;

	bool mColliding;
	bool mCollidingBottom;
	bool mCollidingTop;
	bool mCollidingLeft;
	bool mCollidingRight;


	virtual void AddGravity(float deltaTime);
	virtual void ViewportCollision(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Jump();

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

private:

	bool mMovingLeft;
	bool mMovingRight;

	FACING mFacingDirection;

};
#endif //_CHARACTER_H