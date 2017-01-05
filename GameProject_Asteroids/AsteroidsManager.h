#pragma once
#include "Asteroid.h"
#include "Player.h"
#define ASTEROID_RADIUS 50
#define PLAYER_RADIUS 15

class AsteroidsManager
{
public:
	AsteroidsManager();
	AsteroidsManager(int numAsteroids, Player &_player);
	~AsteroidsManager();
	void Update();
	void Draw();
private:
	Asteroid* asteroidsPool;
	Player* player;
	int numAsteroids;
	void  CollisionController();
};
