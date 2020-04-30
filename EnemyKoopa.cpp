#include "EnemyKoopa.h"
#include "Texture2D.h"
#include "Constants.h"
#include "SoundEffect.h"

using namespace::std;

EnemyKoopa::EnemyKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map) {

	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath)) {
		cout << "Failed to load character texture!" << endl;
	}

	mFacingDirection = startFacing;
	
	mMovementSpeed = movementSpeed;

	mPosition = startPosition;

	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingeSpriteHeight = mTexture->GetHeight();

}
EnemyKoopa::~EnemyKoopa() {

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
	cout << "!" << endl;
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



}

