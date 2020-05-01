#pragma once
#ifndef _PLAYER_H
#define _PLAYER_H

#include "SDL.h"
#include <iostream>
#include <string>
#include "LevelMap.h"
#include "Character.h"
#include "SoundEffect.h"

using namespace::std;

class Texture2D;

class Player : public Character{

public:

	Player(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Player();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();

protected:

	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	Mix_Chunk* sound;

	float mCollisionRadius;

	bool mColliding;
	bool mCollidingBottom;
	bool mCollidingTop;
	bool mCollidingLeft;
	bool mCollidingRight;

	virtual void AddGravity(float deltaTime);
	virtual void Collision(float deltaTime);
	virtual void Jump(float deltaTime);

	virtual void Movement(float deltaTime);

private:

	bool mMovingLeft;
	bool mMovingRight;
	bool mMoveLeft;
	bool mMoveRight;

	float velocity;
	float acceleration = 0.02f;


	LevelMap* mCurrentLevelMap;

	FACING mFacingDirection;

};
#endif //_PLAYER_H