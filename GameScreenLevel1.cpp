#include "GameScreenLevel1.h"
#include "GameScreen.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "Progression.h"
#include "time.h"


GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {

	mRenderer = renderer;
	InitLevel();

	EnemyKoopa* koopaEnemy[4];
	Shotgun* superShotgun;

	itemCollected = false;

}

GameScreenLevel1::~GameScreenLevel1() {

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	
	mLevelMap = NULL;

	mEnemies.clear();

}
void GameScreenLevel1::SetLevelMap() {

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

bool GameScreenLevel1::InitLevel() {

	SetLevelMap();

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Level1.png")) {
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	myCharacter = new Player(mRenderer, "Images/Mario.png", Vector2D(64, 330),mLevelMap);


	srand(time(NULL));

	int upperWidth = SCREEN_WIDTH;
	int lowerWidth = 0;
	int upperHeight = -20;
	int lowerHeight = -10;

	

	for (int i = 0; i < 4; i++) {

		int a = rand() % 2;
		if (a == 1) {
			koopaEnemy[i] = new EnemyKoopa(mRenderer, "Images/Koopa.png", mLevelMap, Vector2D((rand() % (upperWidth - lowerWidth + 1)) + lowerWidth, (rand() % (upperHeight - lowerHeight + 1)) + lowerHeight), FACING_LEFT, 0.2f,2);
		}
		else {
			koopaEnemy[i] = new EnemyKoopa(mRenderer, "Images/Koopa.png", mLevelMap, Vector2D((rand() % (upperWidth - lowerWidth + 1)) + lowerWidth, (rand() % (upperHeight - lowerHeight + 1)) + lowerHeight), FACING_RIGHT, 0.2f,2);
		}
	}

	superShotgun = new Shotgun(mRenderer, "Images/shotgunSmall.png", mLevelMap, Vector2D(230, 125), FACING_LEFT, 0.0f, 1);

	return true;

}

void GameScreenLevel1::Render(){ 
	
	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->Render();
	}

	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	myCharacter->Render();
	for (int i = 0; i < 4; i++) {
		koopaEnemy[i]->Render();
	}
	if (!itemCollected) {
		superShotgun->Render();
	}

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e){
	
	if (!itemCollected) {
		if (myCharacter->GetPosition().x > 220 && myCharacter->GetPosition().x < 250 && myCharacter->GetPosition().y > 110 && myCharacter->GetPosition().y < 130) {
			canProgress = true;
			itemCollected = true;
			PlaySound("Audio/Powerup.wav", 0);
		}
	}
	if (canProgress && myCharacter->GetPosition().x > 450 && myCharacter->GetPosition().x < 480 && myCharacter->GetPosition().y > 24 && myCharacter->GetPosition().y < 26) {
		pipeEntered = true;
	}

	myCharacter->Update(deltaTime, e);

	for (int i = 0; i < 4; i++) {
		koopaEnemy[i]->Update(deltaTime, e);
	}
	superShotgun->Update(deltaTime, e);

}