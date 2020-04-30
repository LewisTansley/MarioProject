#include <iostream>
#include "SDL/image_include/SDL_image.h"
#include "SDL/include/SDL.h"
#include "SDL/mixer_include/SDL_mixer.h"
#include "GameScreenManager.h"
#include "source.h"
#include <string>

using namespace::std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameScreenManager* gameScreenManager;

Mix_Music* gMusic = NULL;

float oldTime;
float deltaTime;
float newTime;

void LoadMusic();

Game::Game(int argc, char* argv[]) {

	bool quit = false;

	if (InitSDL()) {

		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_INTRO);

		//cout << "startTime" << "   " << "deltaTime(ms)" << "   " << "SDL_GetTicks()" << endl;

		oldTime = SDL_GetTicks();

		while (!quit) {

			newTime = SDL_GetTicks();
			deltaTime = newTime - oldTime;

			Render();

			quit = Update();

			//SDL_Delay(1);

			oldTime = newTime;

			//cout << "   " << oldTime << "            " << deltaTime << "              " << SDL_GetTicks() << endl;

		}

		CloseSDL();

	}
}

Game::~Game(void) {}

void LoadMusic(string path) {

	gMusic = Mix_LoadMUS(path.c_str());

	if (gMusic == NULL) {
		cout << "Failed to load Music! Error: " << Mix_GetError() << endl;
	}

}

bool Game::InitSDL() {

	SDL_Init(SDL_INIT_EVENTS);

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

		
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			cout << "Mixer failed to initiliase. ERROR: " << Mix_GetError() << endl;
			return false;
		}

		LoadMusic("Audio/ADG8BIT.mp3");
		currentMusic = SCREEN_INTRO;

		if (Mix_PlayingMusic() == 0) {
			Mix_PlayMusic(gMusic, 0);
		}

		SDL_Delay(1);
		return true;

	}

}

bool Game::Update() {

	if (Mix_PlayingMusic() == 0 && gameScreenManager->activeScreen == SCREEN_INTRO) {
		gameScreenManager->ChangeScreen(SCREEN_MENU);
	}
	if (currentMusic == SCREEN_INTRO && gameScreenManager->activeScreen == SCREEN_MENU) {
		currentMusic = SCREEN_MENU;
		LoadMusic("Audio/ADG.mp3");
		Mix_PlayMusic(gMusic, -1);
	}
	if (Mix_PlayingMusic() == 1 && currentMusic == SCREEN_MENU && gameScreenManager->activeScreen == SCREEN_LEVEL1) {
		currentMusic = SCREEN_LEVEL1;
		LoadMusic("Audio/MarioTheme.mp3");
		Mix_PlayMusic(gMusic, -1);
	}
	if (Mix_PlayingMusic() == 1 && currentMusic == SCREEN_LEVEL1 && gameScreenManager->activeScreen == SCREEN_LEVEL2) {
		currentMusic = SCREEN_LEVEL2;
		LoadMusic("Audio/TOTTFIY8BIT.mp3");
		Mix_PlayMusic(gMusic, -1);
	}

	SDL_Event e;

	SDL_PollEvent(&e);

		switch (e.type) {
		
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
					case SDLK_q:
						return true;
 					break;
				}
			break;
			case SDL_QUIT:
				return true;
			break;
		}
	
	gameScreenManager->Update(deltaTime, e);

	return false;

}

void Game::Render() {

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);
	
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