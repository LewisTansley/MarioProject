#include "Shotgun.h"
#include "Texture2D.h"
#include "Constants.h"
#include "SoundEffect.h"

using namespace::std;

int mFrameDelay = 1000;
int mCurrentFrame = 0;

Shotgun::Shotgun(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed, int tiles) : Character(renderer, imagePath, startPosition, map) {

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

	GetSpriteCount = tiles;

}
Shotgun::~Shotgun() {

}

void Shotgun::Render() {

	int left;

	if (GetSpriteCount > 1) {
		left = mCurrentFrame * mSingleSpriteWidth;
	}
	else {
		left = 0;
	}

	if (mInjured) {
		left = mSingleSpriteWidth;
	}

	SDL_Rect portionOfSpritesheet = { left, 0,mSingleSpriteWidth,mSingeSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.x),(int)(mPosition.y),mSingleSpriteWidth,mSingeSpriteHeight };

	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE, 0);
	}
	else {
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL, 0);

	}
}
void Shotgun::Update(float deltaTime, SDL_Event e) {

	Character::Update(deltaTime, e);

	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f) {
		cout << "!" << endl;
		mFrameDelay = 1000;
		mCurrentFrame++;
		if (mCurrentFrame > 2) {
			mCurrentFrame = 0;
		}
	}
}

