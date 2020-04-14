#include "GameScreenTitle.h"
#include "GameScreen.h"
#include <iostream>
#include "Texture2D.h"


GameScreenTitle::GameScreenTitle(SDL_Renderer* renderer) : GameScreen(renderer) {

	InitLevel();

}

GameScreenTitle::~GameScreenTitle() {

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	mRenderer = NULL;
}

bool GameScreenTitle::InitLevel() {

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	return true;

}

void GameScreenTitle::Render() {

	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

}

void GameScreenTitle::Update(float deltaTime, SDL_Event e) {}