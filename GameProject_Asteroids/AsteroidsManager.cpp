#include "AsteroidsManager.h"




AsteroidsManager::AsteroidsManager(int _numAsteroids, Player& _player)
{
	numAsteroids = _numAsteroids;
	player = &_player;
	asteroidsPool = new Asteroid[numAsteroids];

}

AsteroidsManager::~AsteroidsManager()
{
	//delete[] asteroidsPool;
}

void AsteroidsManager::Update()
{
	for (int i = 0; i < numAsteroids; i++) {
		asteroidsPool[i].Update(TM.GetDeltaTime() / 100000);
		CollisionController(asteroidsPool[i]);
	}
}

void AsteroidsManager::CollisionController(Asteroid& currentAsteroid)
{
	Bullets* currentBullet;
	Vector2D distanceFromAsteroid;
	float distance;
	//Player Collisions
	distanceFromAsteroid.x = player->GetPosition().x - currentAsteroid.GetPosition().x;
	distanceFromAsteroid.y = player->GetPosition().y  - currentAsteroid.GetPosition().y;

	distance = distanceFromAsteroid.Length();
	if (distance <= PLAYER_RADIUS+ASTEROID_RADIUS) {
		player->lifes--;
		player->Reset();
	}

	//BulletCollisions
	for (int j = 0; j < MAX_BULLETS; j++) {
		currentBullet = &player->GetCurrentBullet(j);
		if (currentBullet->isActive) {
			distanceFromAsteroid.x = currentBullet->GetPosition().x - currentAsteroid.GetPosition().x;
			distanceFromAsteroid.y = currentBullet->GetPosition().y - currentAsteroid.GetPosition().y;
			distance = distanceFromAsteroid.Length();
			if (distance <= ASTEROID_RADIUS) {
				//Bullet Impact
				currentBullet->Reset();
				DivideAsteroid(currentAsteroid);
			}
		}
	}
}

void AsteroidsManager::DivideAsteroid(Asteroid & currentAsteroid)
{
	if (currentAsteroid.asteroidState == "BIG") {
		player->points += 20;
		currentAsteroid.ChangeSprite(ObjectID::MEDIUM_ASTEROID1, 39, 39);
		currentAsteroid.asteroidState = "MEDIUM";
		currentAsteroid.speed *= 3;
		currentAsteroid.RandomizeDirection();

		numAsteroids++;
		Asteroid* temp = new Asteroid[numAsteroids];
		for (int i = 0; i < numAsteroids - 1; i++) {
			temp[i] = asteroidsPool[i];
		}
		temp[numAsteroids-1] = currentAsteroid;
		temp[numAsteroids - 1].RandomizeDirection();
		asteroidsPool = temp;
		//delete[] temp;
	}
	else if (currentAsteroid.asteroidState == "MEDIUM") {
		player->points += 50;
		currentAsteroid.ChangeSprite(ObjectID::SMALL_ASTEROID1, 20, 20);
		currentAsteroid.asteroidState = "SMALL";
		currentAsteroid.RandomizeDirection();

		numAsteroids++;
		Asteroid* temp = new Asteroid[numAsteroids];
		for (int i = 0; i < numAsteroids - 1; i++) {
			temp[i] = asteroidsPool[i];
		}
		temp[numAsteroids - 1] = currentAsteroid;
		temp[numAsteroids - 1].InverseDirection();
		asteroidsPool = temp;
		//delete[] temp;

	}
	else if (currentAsteroid.asteroidState == "SMALL") {
		player->points += 100;
		currentAsteroid.Setup();
	}
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
		//	points[j] = { { int(asteroidsPool[i].GetPosition().x + asteroidsPool[i].width/2*cos(j*DEG2RAD)),int(asteroidsPool[i].GetPosition().y + asteroidsPool[i].width/2*sin(j*DEG2RAD)), 8,8 }, 0, ObjectID::BULLET };
		//	points[j].Draw();
		//}

		asteroidsPool[i].Draw();
	}
}

