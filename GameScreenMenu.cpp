#include "GameScreenMenu.h"
#include "GameScreen.h"
#include <iostream>
#include "Texture2D.h"


GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer) {

	InitLevel();

}

GameScreenMenu::~GameScreenMenu() {

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	mRenderer = NULL;
}

bool GameScreenMenu::InitLevel() {

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/MenuBackground.png")) {
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	return true;

}

void GameScreenMenu::Render() {

	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

}

void GameScreenMenu::Update(float deltaTime, SDL_Event e) {}