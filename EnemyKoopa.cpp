#include "EnemyKoopa.h"
#include "Texture2D.h"
#include "Constants.h"
#include "SoundEffect.h"

using namespace::std;

EnemyKoopa::EnemyKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed, int tiles) : Character(renderer, imagePath, startPosition, map) {

	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath)) {
		cout << "Failed to load character texture!" << endl;
	}

	mFacingDirection = startFacing;
	
	mMovementSpeed = movementSpeed;

	mPosition = startPosition;

	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / tiles;
	mSingeSpriteHeight = mTexture->GetHeight();

	mCurrentLevelMap = map;

}
EnemyKoopa::~EnemyKoopa() {

}

void EnemyKoopa::Collision(float deltaTime) {

	if (mCollidingBottom) {
		mCanJump = true;
	}
	else {
		mCanJump = false;
	}
}

void EnemyKoopa::AddGravity(float deltaTime) {

	mPosition.y += 0.5f * deltaTime;
	mCollidingBottom = false;
}

void EnemyKoopa::TakeDamage() {

	mInjured = true;
	mInjuredTime = 2.5f;

	Jump();

}

void EnemyKoopa::Jump() {

	if (!mJumping) {
		mJumpForce = 10.0f;

		mJumping = true;
		mCanJump = false;

	}

}
void EnemyKoopa::FlipRightWayUp() {

	if (mFacingDirection == FACING_LEFT) {
		mFacingDirection = FACING_RIGHT;
	}
	else {
		mFacingDirection = FACING_LEFT;
	}
	mInjured = false;
	Jump();
}
void EnemyKoopa::Render() {

	int left = 0.0f;

	if (mInjured) {
		left = mSingleSpriteWidth;
	}

	SDL_Rect portionOfSpritesheet = { left, 0,mSingleSpriteWidth,mSingeSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.x),(int)(mPosition.y),mSingleSpriteWidth,mSingeSpriteHeight };

	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE,0);
	}
	else {
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL,0);

	}
	//cout << "!" << endl;
}
void EnemyKoopa::Update(float deltaTime, SDL_Event e) {

	Character::Update(deltaTime, e);

	if (!mInjured) {
		if (mFacingDirection == FACING_LEFT) {
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT) {
			mMovingRight = true;
			mMovingLeft = false;
		}
	}
	else {
		mMovingLeft = false;
		mMovingRight = false;
		mInjuredTime -= deltaTime;
		if (mInjuredTime <= 0.0f) {
			FlipRightWayUp();
		}
	}

	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y - 2 + mTexture->GetHeight()) / TILE_HEIGHT;

	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0) {
		AddGravity(deltaTime);
	}
	else {
		mCollidingBottom = true;
	}

	Collision(deltaTime);

	if (velocity < 0.1f) {
		velocity += acceleration * (deltaTime / 64);
	}

	if (mFacingDirection == FACING_LEFT) {
		mPosition.x -= velocity * deltaTime;
	}
	else if(mFacingDirection == FACING_RIGHT){
		mPosition.x += velocity * deltaTime;
	}

	if ((mPosition.x + (mTexture->GetWidth() / 2)) < 0) {
		mPosition.x = SCREEN_WIDTH - (mTexture->GetWidth() / 2);
		SDL_Delay(1);
	}
	if (mPosition.x > SCREEN_WIDTH) {
		mPosition.x = 0 - (mTexture->GetWidth() / 2);
		SDL_Delay(1);
	}

}

