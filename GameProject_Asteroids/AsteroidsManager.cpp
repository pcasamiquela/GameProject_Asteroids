#include "AsteroidsManager.h"




AsteroidsManager::AsteroidsManager(int _numAsteroids, Player &_player)
{
	numAsteroids = _numAsteroids;
	player = &_player;
	asteroidsPool = new Asteroid[numAsteroids];

}

AsteroidsManager::~AsteroidsManager()
{
}

void AsteroidsManager::Update()
{
	for (int i = 0; i < numAsteroids; i++) asteroidsPool[i].Update(TM.GetDeltaTime() / 100000);
}

void AsteroidsManager::CollisionController()
{
	for (int i = 0; i < numAsteroids; i++) {

	}
}

void AsteroidsManager::Draw()
{
	for (int i = 0; i < numAsteroids; i++) {
		asteroidsPool[i].Draw();
	}
}

