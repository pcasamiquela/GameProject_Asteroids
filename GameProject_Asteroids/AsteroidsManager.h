#pragma once
#include "Asteroid.h"
#include "Player.h"
#define ASTEROID_RADIUS currentAsteroid.width/2
#define PLAYER_RADIUS 15

class AsteroidsManager
{
public:
	AsteroidsManager(int numAsteroids, Player &_player, float asteroidsVelocity, float _incrementalSpeed);
	~AsteroidsManager();
	void Update();
	void Draw();
private:
	Asteroid* asteroidsPool;
	Player* player;
	int numAsteroids;
	float incrementalSpeed;
	float timeLapse;

	void  CollisionController(Asteroid& currentAsteroid);
	void DivideAsteroid(Asteroid& currentAsteroid);
	void CreateAsteroidFromAsteroid(Asteroid& currentAsteroid);
	void CreateAsteroid();
	void DeleteAsteroid(Asteroid& currentAsteroid);
};

