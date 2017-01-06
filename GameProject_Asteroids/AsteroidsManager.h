#pragma once
#include "Asteroid.h"
#include "Player.h"
#define ASTEROID_RADIUS currentAsteroid.width/2
#define PLAYER_RADIUS 15

class AsteroidsManager
{
public:
	AsteroidsManager(int numAsteroids, Player &_player, float asteroidsVelocity);
	~AsteroidsManager();
	void Update();
	void Draw();
private:
	Asteroid* asteroidsPool;
	Player* player;
	int numAsteroids;
	void  CollisionController(Asteroid& currentAsteroid);
	void DivideAsteroid(Asteroid& currentAsteroid);
};

