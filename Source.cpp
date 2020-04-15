#include "Constants.h"
#include <iostream>
#include "SDL/image_include/SDL_image.h"
#include "SDL/include/SDL.h"
#include "SDL/mixer_include/SDL_mixer.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include "source.h"

using namespace::std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

GameScreenManager* gameScreenManager;

SDL_Event e;

Game::Game(int argc, char* argv[]) {

	deltaTime = 0;
	gOldTime = 0;

	bool quit = false;

	if (InitSDL()) {

		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);

		gOldTime = SDL_GetTicks();

		while (!quit) {

			Render();
			quit = Update();

		}

		CloseSDL();

	}
}

Game::~Game(void) {}

bool Game::InitSDL() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL did not initialise. ERROR: " << SDL_GetError() << endl;
		return false;
	} 
	
	else {

		gWindow = SDL_CreateWindow("Mario: Eternal",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (gWindow == NULL) {
			cout << "Window did not initialise. ERROR: " << SDL_GetError() << endl;
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		if (gRenderer != NULL) {

			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags)) {
				cout << "SDL_Image failed to initiliase. ERROR: " << IMG_GetError() << endl;
				return false;
			}

		} 
		
		else {
			cout << "Renderer failed to initialise. ERROR: " << SDL_GetError() << endl;
			return false;
		}


		return true;

	}

}

bool Game::Update() {

	deltaTime = SDL_GetTicks();

	SDL_PollEvent(&e);

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
				return true;
				break;
			}
			break;
		case SDL_QUIT:
			return true;
			break;
		}
	}

	gameScreenManager->Update((float)(deltaTime - gOldTime) / 1000.0f, e);

	gOldTime = deltaTime;

	cout << "tick " << deltaTime << endl;

	return false;

}

void Game::Render() {

	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	
	gameScreenManager->Render();

	SDL_RenderPresent(gRenderer);

}

void Game::CloseSDL() {
	
	delete gameScreenManager;
	gameScreenManager = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();

}