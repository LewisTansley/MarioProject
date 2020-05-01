#pragma once
#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H

#include <SDL.h>
#include "GameScreen.h"
#include "Player.h"
#include "LevelMap.h"
#include "EnemyKoopa.h"
#include "Projectile.h"


class Texture2D;
class Player;

class GameScreenLevel2 : GameScreen {

public:

	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* mBackgroundTexture;
	Player* myCharacter;

	EnemyKoopa* koopaEnemy[50];

	bool shooting;

	Projectile* projectile;

	void SetLevelMap();

	LevelMap* mLevelMap;

	bool InitLevel();

};

#endif //_GAMESCREENLEVEL2_H
