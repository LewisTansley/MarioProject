#pragma once
#ifndef _ENEMYKOOPA_H
#define _ENEMYKOOPA_H

#include "SDL.h"
#include <iostream>
#include <string>
#include "LevelMap.h"
#include "Character.h"
#include "SoundEffect.h"

using namespace::std;

class Texture2D;

class EnemyKoopa : public Character{

public:

	EnemyKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed);
	~EnemyKoopa();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();

	void TakeDamage();
	void Jump();

protected:

	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	float mCollisionRadius;

private:

	bool mMovingLeft;
	bool mMovingRight;

	float mSingleSpriteWidth;
	float mSingeSpriteHeight;

	void FlipRightWayUp();

	bool mInjured;

	float mInjuredTime;

	LevelMap* mCurrentLevelMap;

	FACING mFacingDirection;

	float mMovementSpeed;

};
#endif //_ENEMYKOOPA_H