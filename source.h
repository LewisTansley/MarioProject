#pragma once
#ifndef _SOURCE_H
#define _SOURCE_H

#include "Constants.h"
#include <iostream>
#include "SDL/image_include/SDL_image.h"
#include "SDL/include/SDL.h"
#include "SDL/mixer_include/SDL_mixer.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
#include <string>

using namespace::std;

class Game {
public:

	Game(int argc, char* argv[]);
	~Game(void);

	bool InitSDL();
	void CloseSDL();
	bool Update();
	void Render();

	SCREENS currentMusic;

private:

protected:



};

#endif //_SOURCE_H