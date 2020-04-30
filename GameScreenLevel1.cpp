#include "GameScreenLevel1.h"
#include "GameScreen.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "Progression.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {

	mRenderer = renderer;
	InitLevel();

	EnemyKoopa* koopaEnemy;

}

GameScreenLevel1::~GameScreenLevel1() {

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	
	mLevelMap = NULL;

	//delete myCharacter;
	//myCharacter = NULL;

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

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, 0.5f);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, 0.5f);

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Level1.png")) {
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	myCharacter = new Player(mRenderer, "Images/Mario.png", Vector2D(64, 330),mLevelMap);



	return true;

}

void GameScreenLevel1::Render(){ 
	
	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->Render();
	}

	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	myCharacter->Render();

}

//void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e) {
//
//	if (!mEnemies.empty()) {
//		int enemyIndexToDelete = -1;
//		for (unsigned int i = 0; i < mEnemies.size(); i++) {
//			if (mEnemies[i]->GetPosition().y > 300.0f) {
//				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionRadius.width * 0.5f) || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionRadius().width * 0.55f)) {
//					//mEnemies[i]->SetAlive(false);
//				}
//			}
//			mEnemies[i]->Update(deltaTime, e);
//
//			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition.x > SCREEN_WIDTH - 96.0f)) {
//
//			}
//			else {
//				if () {
//
//				}
//			}
//			if (!mEnemies[i]->GetAlive()) {
//				enemyIndexToDelete = i;
//			}
//		}
//		if (enemyIndexToDelete != -1) {
//			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
//		}
//	}
//
//}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed) {

	koopaEnemy = new EnemyKoopa(mRenderer, "Images/Koopa.png", mLevelMap, position, direction, speed);

	mEnemies.push_back(koopaEnemy);

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e){

	//if (Collisions::Instance()->Circle(myCharacter, myCharacter)) {
	//} 

	//UpdateEnemies(deltaTime, e);

	if (myCharacter->GetPosition().x > 210 && myCharacter->GetPosition().x < 264 && myCharacter->GetPosition().y > 110 && myCharacter->GetPosition().y < 130) {
		canProgress = true;
	}
	//cout << "gsl1: " << canProgress << endl;;

	myCharacter->Update(deltaTime, e);
		
}