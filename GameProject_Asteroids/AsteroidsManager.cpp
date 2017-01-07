#include "AsteroidsManager.h"




AsteroidsManager::AsteroidsManager(int _numAsteroids, Player& _player, float asteroidsVelocity, float _incrementalSpeed)
{
	numAsteroids = _numAsteroids;
	player = &_player;
	incrementalSpeed = _incrementalSpeed;
	timeLapse = 0;

	asteroidsPool = new Asteroid[numAsteroids];
	for (int i = 0; i < numAsteroids; i++) {
		asteroidsPool[i].speed = asteroidsVelocity;
		asteroidsPool[i].id = i;
	}
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
		asteroidsPool[i].playerPosition = player->GetPosition();
	}
	if (IM.IsKeyDown<MOUSE_BUTTON_MIDDLE>())CreateAsteroid();
	timeLapse += TM.GetDeltaTime()*0.001f;
	if (timeLapse >= incrementalSpeed) {
		CreateAsteroid();
		timeLapse = 0;
	}
}

void AsteroidsManager::CollisionController(Asteroid& currentAsteroid)
{
	Bullets* currentBullet;
	Vector2D distanceFromAsteroid;
	float distance;
	//Player Collisions
	if (!player->inmortal) {
		distanceFromAsteroid.x = player->GetPosition().x - currentAsteroid.GetPosition().x;
		distanceFromAsteroid.y = player->GetPosition().y - currentAsteroid.GetPosition().y;

		distance = distanceFromAsteroid.Length();
		if (distance <= PLAYER_RADIUS + ASTEROID_RADIUS) {
			player->lifes--;
			player->Reset();
		}
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
		player->score += 20;
		currentAsteroid.ChangeSprite(ObjectID::MEDIUM_ASTEROID1, 39, 39);
		currentAsteroid.asteroidState = "MEDIUM";
		currentAsteroid.speed *= 3;
		currentAsteroid.RandomizeDirection();
		CreateAsteroidFromAsteroid(currentAsteroid);
	}
	else if (currentAsteroid.asteroidState == "MEDIUM") {
		player->score += 50;
		currentAsteroid.ChangeSprite(ObjectID::SMALL_ASTEROID1, 20, 20);
		currentAsteroid.asteroidState = "SMALL";
		currentAsteroid.RandomizeDirection();
		CreateAsteroidFromAsteroid(currentAsteroid);

	}
	else if (currentAsteroid.asteroidState == "SMALL") {
		player->score += 100;
		DeleteAsteroid(currentAsteroid);
	}
}


void AsteroidsManager::CreateAsteroid()
{
	numAsteroids++;

	Asteroid* temp = new Asteroid[numAsteroids];
	for (int i = 0; i < numAsteroids - 1; i++) {
		temp[i] = asteroidsPool[i];
	}
	temp[numAsteroids - 1].Setup();
	temp[numAsteroids - 1].id = numAsteroids - 1;
	asteroidsPool = temp;

	//delete[] temp;
}

void AsteroidsManager::CreateAsteroidFromAsteroid(Asteroid& currentAsteroid)
{
	numAsteroids++;
	Asteroid* temp = new Asteroid[numAsteroids];
	for (int i = 0; i < numAsteroids - 1; i++) {
		temp[i] = asteroidsPool[i];
	}
	temp[numAsteroids - 1] = currentAsteroid;
	temp[numAsteroids - 1].id = numAsteroids - 1;
	temp[numAsteroids - 1].InverseDirection();
	asteroidsPool = temp;

	//delete[] temp;
}



void AsteroidsManager::DeleteAsteroid(Asteroid & currentAsteroid)
{
	int it = 0;
	bool eliminated = false;
	numAsteroids--;
	Asteroid* temp = new Asteroid[numAsteroids];
	for (int i = 0; i < numAsteroids; i++) {
		if (i == currentAsteroid.id) {
			it++;
			eliminated = true;
		}
		temp[i] = asteroidsPool[it];
		if (eliminated) temp[i].id--;
		it++;
	}

	asteroidsPool = temp;
	//delte[] temp;
}


void AsteroidsManager::Draw()
{
	Sprite* score = new Sprite[360];

	//Render Player Sphere Collision

	//for (int j = 0; j < 360; j++) {
	//	score[j] = { { int(player->GetPosition().x + PLAYER_RADIUS*cos(j*DEG2RAD)),int(player->GetPosition().y + PLAYER_RADIUS*sin(j*DEG2RAD)), 8,8 }, 0, ObjectID::BULLET };
	//	score[j].Draw();
	//}

	for (int i = 0; i < numAsteroids; i++) {

		//Render Asteroids Sphere Collsion

		//for (int j = 0; j < 360; j++) {
		//	score[j] = { { int(asteroidsPool[i].GetPosition().x + asteroidsPool[i].width/2*cos(j*DEG2RAD)),int(asteroidsPool[i].GetPosition().y + asteroidsPool[i].width/2*sin(j*DEG2RAD)), 8,8 }, 0, ObjectID::BULLET };
		//	score[j].Draw();
		//}

		asteroidsPool[i].Draw();
	}
}

