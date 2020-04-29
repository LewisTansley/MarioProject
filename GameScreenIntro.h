#pragma once
#ifndef _GAMESCREENINTRO_H
#define _GAMESCREENINTRO_H

#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"
#include "Player.h"

class Texture2D;

class GameScreenIntro : GameScreen {

public:

	GameScreenIntro(SDL_Renderer* renderer);
	~GameScreenIntro();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* mBackgroundTexture;
	Player* myCharacter;

	bool InitLevel();

};

#endif //_GAMESCREENINTRO_H
