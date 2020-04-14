#pragma once
#ifndef _GAMESCREENLEVEL_1_H
#define _GAMESCREENLEVEL_1_H

#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"

class Texture2D;
class Character;

class GameScreenLevel1 : GameScreen {

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* mBackgroundTexture;
	Character* myCharacter;

	bool InitLevel();

};

#endif //_GAMESCREENLEVEL_1_H
