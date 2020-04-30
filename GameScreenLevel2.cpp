#include "GameScreenLevel2.h"
#include "GameScreen.h"
#include <iostream>
#include "Texture2D.h"


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

	return true;

}

void GameScreenLevel2::Render() {

	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	myCharacter->Render();

}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e) {

	myCharacter->Update(deltaTime, e);

}