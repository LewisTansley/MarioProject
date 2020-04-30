#pragma once
#ifndef _GAMESCREENLEVEL_1_H
#define _GAMESCREENLEVEL_1_H

#include <SDL.h>
#include "GameScreen.h"
#include "Player.h"
#include "LevelMap.h"
#include "EnemyKoopa.h"
#include <vector>

class Texture2D;
class Player;

class GameScreenLevel1 : GameScreen {

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

private:
	Texture2D* mBackgroundTexture;
	Player* myCharacter;
	EnemyKoopa* koopaEnemy;

	void SetLevelMap();

	LevelMap* mLevelMap;

	bool InitLevel();

	vector<EnemyKoopa*>mEnemies;

};

#endif //_GAMESCREENLEVEL_1_H
