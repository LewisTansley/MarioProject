#include "GameScreen.h"

void GameScreen::Render() {}

void GameScreen::Update(float deltaTime, SDL_Event e) {}

GameScreen::GameScreen(SDL_Renderer* renderer) {

	mRenderer = renderer;

}

GameScreen::~GameScreen() {

	mRenderer = NULL;

}