#pragma once
#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H

#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"

class Texture2D;

class GameScreenMenu : GameScreen {

public:

	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* mBackgroundTexture;

	bool InitLevel();

};

#endif //_GAMESCREENMENU_H
