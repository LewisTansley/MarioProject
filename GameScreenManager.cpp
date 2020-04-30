#include "GameScreen.h"
#include "GameScreenManager.h"
#include "GameScreenIntro.h"
#include "GameScreenMenu.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "Commons.h"
#include "Progression.h"

bool canProgress = false;
bool pipeEntered = false;


GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {

	mRenderer = renderer;
	mCurrentScreen = NULL;
	ChangeScreen(startScreen);
	activeScreen = startScreen;

	canChangeScreen = true;


}



void GameScreenManager::Render() { 

	mCurrentScreen->Render();

}

void GameScreenManager::Update(float deltaTime, SDL_Event e) {

	//cout << "gsm: " << canProgress;

	if (pipeEntered == 1) {
			canProgress = false;
			pipeEntered = false;
			ChangeScreen(SCREEN_LEVEL2);
			canChangeScreen = false;
	}

	switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
				case SDLK_SPACE:
					if (activeScreen == SCREEN_INTRO) {
						if (canChangeScreen == true) {
							ChangeScreen(SCREEN_MENU);
							canChangeScreen = false;
						}
					}
					if (activeScreen == SCREEN_MENU) {
						if (canChangeScreen == true) {
							ChangeScreen(SCREEN_LEVEL1);
							canChangeScreen = false;
						}
					}
				break;
			}
		break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
			case SDLK_SPACE:
				if (activeScreen != SCREEN_LEVEL1) {
					canChangeScreen = true;
				}
			break;
			}
	}

	mCurrentScreen->Update(deltaTime, e);

}

void GameScreenManager::ChangeScreen(SCREENS newScreen) {

	if (mCurrentScreen != NULL) {
		delete mCurrentScreen;
	}

	GameScreenIntro* tempScreen0;
	GameScreenMenu* tempScreen1;
	GameScreenLevel1* tempScreen2;
	GameScreenLevel2* tempScreen3;

	switch (newScreen) {
		case SCREEN_INTRO:
			tempScreen0 = new GameScreenIntro(mRenderer);
			mCurrentScreen = (GameScreen*)tempScreen0;
			tempScreen0 = NULL;
			activeScreen = SCREEN_INTRO;
		break;
		case SCREEN_MENU:
			tempScreen1 = new GameScreenMenu(mRenderer);
			mCurrentScreen = (GameScreen*)tempScreen1;
			tempScreen1 = NULL;
			activeScreen = SCREEN_MENU;

		break;
		case SCREEN_LEVEL1:
			tempScreen2 = new GameScreenLevel1(mRenderer);
			mCurrentScreen = (GameScreen*)tempScreen2;
			tempScreen2 = NULL;
			activeScreen = SCREEN_LEVEL1;

		break;
		case SCREEN_LEVEL2:
			tempScreen3 = new GameScreenLevel2(mRenderer);
			mCurrentScreen = (GameScreen*)tempScreen3;
			tempScreen3 = NULL;
			activeScreen = SCREEN_LEVEL2;

		break;
	}

}

GameScreenManager::~GameScreenManager() {

	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}