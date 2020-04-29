#include "GameScreenIntro.h"
#include "GameScreen.h"
#include <iostream>
#include "Texture2D.h"
#include "GameScreenManager.h"

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer) {

	mRenderer = renderer;

	InitLevel();

}

GameScreenIntro::~GameScreenIntro() {

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

}

bool GameScreenIntro::InitLevel() {

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/IntroBackground.png")) {
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	return true;

}

void GameScreenIntro::Render() {

	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

}

void GameScreenIntro::Update(float deltaTime, SDL_Event e) {}