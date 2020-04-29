#include "GameScreenLevel1.h"
#include "GameScreen.h"
#include <iostream>
#include "Texture2D.h"


GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {

	mRenderer = renderer;

	InitLevel();

}

GameScreenLevel1::~GameScreenLevel1() {

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	
	//delete myCharacter;
	//myCharacter = NULL;

}

bool GameScreenLevel1::InitLevel() {

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	myCharacter = new Player(mRenderer, "Images/Mario.png", Vector2D(64, 330));

	return true;

}

void GameScreenLevel1::Render(){ 
	
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	myCharacter->Render();

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e){

	myCharacter->Update(deltaTime, e);

}