#pragma once
#ifndef _GAMESCREENTITLE_H
#define _GAMESCREENTITLE_H

#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"

class Texture2D;

class GameScreenTitle : GameScreen {

public:

	GameScreenTitle(SDL_Renderer* renderer);
	~GameScreenTitle();

	void Render();
	void Update(float tick, SDL_Event e);

private:
	Texture2D* mBackgroundTexture;

	bool InitLevel();

};

#endif //_GAMESCREENTITLE_H
