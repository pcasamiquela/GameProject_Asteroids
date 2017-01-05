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
	//for (int i = 0; i < numAsteroids; i++) asteroidsPool[i].Update(TM.GetDeltaTime() / 100000);
	CollisionController();
}

void AsteroidsManager::CollisionController()
{
	//Player COllisions
	Vector2D distancePlayerAsteroid;
	for (int i = 0; i < numAsteroids; i++) {
		distancePlayerAsteroid.x = (player->GetPosition().x) - (asteroidsPool[i].GetPosition().x);
		distancePlayerAsteroid.y = (player->GetPosition().y)  - (asteroidsPool[i].GetPosition().y);

		float distance = distancePlayerAsteroid.Length();
		
		if (distance <= PLAYER_RADIUS+ASTEROID_RADIUS) {
			player->lifes--;
			player->Reset();
		}
	}

	//BulletCollisions
	//for(int i = 0; i < )
}

void AsteroidsManager::Draw()
{
	Sprite* points = new Sprite[360];

	//Render Player Sphere Collision

	//for (int j = 0; j < 360; j++) {
	//	points[j] = { { int(player->GetPosition().x + PLAYER_RADIUS*cos(j*DEG2RAD)),int(player->GetPosition().y + PLAYER_RADIUS*sin(j*DEG2RAD)), 8,8 }, 0, ObjectID::BULLET };
	//	points[j].Draw();
	//}

	for (int i = 0; i < numAsteroids; i++) {

		//Render Asteroids Sphere Collsion

		//for (int j = 0; j < 360; j++) {
		//	points[j] = { { int(asteroidsPool[i].GetPosition().x + ASTEROID_RADIUS*cos(j*DEG2RAD)),int(asteroidsPool[i].GetPosition().y + ASTEROID_RADIUS*sin(j*DEG2RAD)), 8,8 }, 0, ObjectID::BULLET };
		//	points[j].Draw();
		//}

		asteroidsPool[i].Draw();
	}
}

