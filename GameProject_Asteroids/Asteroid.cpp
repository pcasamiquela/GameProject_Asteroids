#include "Asteroid.h"



Asteroid::Asteroid()
{
	Setup();
}

void Asteroid::Setup() {
	
	srand(rand());
	position = Vector2D(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT); //Random position inside screen
	randomDirection = Vector2D(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT) - position; //Random Vector
	randomDirection.Normalize();
	width = 92;
	height = 92;
	speed = 0.001f;
	asteroidState = "BIG";
	int randomSprite = rand() % (3) + 1;
	switch (randomSprite)
	{
	case 1:
		asteroidSprite = { { int(position.x),int(position.y),width,height }, 0, ObjectID::BIG_ASTEROID1 };
		break;
	case 2:
		asteroidSprite = { { int(position.x),int(position.y),width,height }, 0, ObjectID::BIG_ASTEROID2 };
		break;
	case 3:
		asteroidSprite = { { int(position.x),int(position.y),width,height }, 0, ObjectID::BIG_ASTEROID3 };
	default:
		break;
	}
}

void Asteroid::ChangeSprite(ObjectID objectID, int newWidth, int newHight)
{
	width = newWidth;
	height = newHight;
	asteroidSprite = { { int(position.x),int(position.y),width,height }, 0, ObjectID::BIG_ASTEROID2 };
}


Vector2D Asteroid::GetPosition()
{
	Vector2D centredPosition;
	centredPosition.x = position.x + width / 2;
	centredPosition.y = position.y + height / 2;
	return centredPosition;
}

void Asteroid::InversDirection()
{
	randomDirection.x *= -1;
	randomDirection.y *= -1;
}



Asteroid::~Asteroid()
{
}

void Asteroid::Update(float deltaTime)
{
	DoWrap(position);
	UpdatePosition(deltaTime);
}

void Asteroid::Draw()
{
	asteroidSprite.Draw();
}

void Asteroid::UpdatePosition(float deltaTime)
{

	position.x += randomDirection.x*speed;
	position.y += randomDirection.y*speed;

	asteroidSprite.transform.x = position.x;
	asteroidSprite.transform.y = position.y;
	
}

void Asteroid::DoWrap(Vector2D & position)
{
	if (position.x > SCREEN_WIDTH + 100)
	{
		position.x = -100.0f;
	}
	else if (position.x < -100)
	{
		position.x = SCREEN_WIDTH + 100;
	}

	if (position.y > SCREEN_HEIGHT + 100)
	{
		position.y = -100.0f;
	}
	else if (position.y < -100.0f)
	{
		position.y = SCREEN_HEIGHT+100.;
	}
}