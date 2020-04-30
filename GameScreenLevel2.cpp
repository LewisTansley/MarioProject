#include "GameScreenLevel2.h"
#include "GameScreen.h"
#include <iostream>
#include "Texture2D.h"
#include <time.h>

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer) {

	mRenderer = renderer;
	InitLevel();

}

GameScreenLevel2::~GameScreenLevel2() {

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	mLevelMap = NULL;

	//delete myCharacter;
	//myCharacter = NULL;

}
void GameScreenLevel2::SetLevelMap() {

	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	if (mLevelMap != NULL) {
		delete mLevelMap;
	}

	mLevelMap = new LevelMap(map);

}

bool GameScreenLevel2::InitLevel() {

	SetLevelMap();

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Level2.png")) {
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	myCharacter = new Player(mRenderer, "Images/MarioGuy.png", Vector2D(64, 330), mLevelMap);

	srand(time(NULL));
	 
	int upperWidth = SCREEN_WIDTH;
	int lowerWidth = 0;
	int upperHeight = -20;
	int lowerHeight = -10;



	for (int i = 0; i < 50; i++) {

		int a = rand() % 2;
		if (a == 1) {
			koopaEnemy[i] = new EnemyKoopa(mRenderer, "Images/KoopaEvil.png", mLevelMap, Vector2D((rand() % (upperWidth - lowerWidth + 1)) + lowerWidth, (rand() % (upperHeight - lowerHeight + 1)) + lowerHeight), FACING_LEFT, 0.2f,3);
		}
		else {
			koopaEnemy[i] = new EnemyKoopa(mRenderer, "Images/KoopaEvil.png", mLevelMap, Vector2D((rand() % (upperWidth - lowerWidth + 1)) + lowerWidth, (rand() % (upperHeight - lowerHeight + 1)) + lowerHeight), FACING_RIGHT, 0.2f,3);
		}
	}

	return true;

}

void GameScreenLevel2::Render() {

	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	myCharacter->Render();
	for (int i = 0; i < 50; i++) {
		koopaEnemy[i]->Render();
	}
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e) {

	switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
				case SDLK_LALT:
					PlaySound("Audio/Shoot.wav", 0);
				break;
			}
		break;
	}

	myCharacter->Update(deltaTime, e);

	for (int i = 0; i < 50; i++) {
		koopaEnemy[i]->Update(deltaTime, e);
	}

}