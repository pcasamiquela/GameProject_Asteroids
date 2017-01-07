#include "Ovni.h"



Ovni::Ovni()
{
}


Ovni::~Ovni()
{
}
void Ovni::Setup() {
	int randCorner = rand() % 4 + 1;
	switch (randCorner)
	{
	case 1:
		position = Vector2D(rand() % SCREEN_WIDTH, rand() % int(playerPosition.y - 150)); //Random position inside up zone
		break;
	case 2:
		position = Vector2D(rand() % int(playerPosition.x - 200), rand() % SCREEN_HEIGHT); //Random position inside left zone
		break;
	case 3:
		position = Vector2D(rand() % SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - int(playerPosition.y + 150)) + int(playerPosition.y + 150)); //Random position inside bottom zone
		break;
	case 4:
		position = Vector2D(rand() % (SCREEN_WIDTH - int(playerPosition.x + 150)) + int(playerPosition.x + 150), rand() % SCREEN_HEIGHT); //Random position right zone
		break;
	}
	ovniSprite = { {int(position.x), int(position.y), 53,30}, 0, ObjectID::OVNI };
	RandomizeDirection();
}


void Ovni::Update(float deltaTime)
{
	DoWrap();
	UpdatePosition(deltaTime);
	bullet.Update(deltaTime, bulletAngle);
	//bullet.firstShoot = false;
}



void Ovni::DoWrap()
{
	if (position.x > SCREEN_WIDTH + 50)
	{
		position.x = -50.0f;
	}
	else if (position.x < -50)
	{
		position.x = SCREEN_WIDTH + 50;
	}

	if (position.y > SCREEN_HEIGHT + 50)
	{
		position.y = -50.0f;
	}
	else if (position.y < -50.0f)
	{
		position.y = SCREEN_HEIGHT + 50.;
	}
}
void Ovni::RandomizeDirection()
{
	randomDirection = Vector2D(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT) - position; //Random Vector
	randomDirection.Normalize();
}
void Ovni::Shoot() {
	bullet.lifeTime = 0;
	bulletAngle = (rand() % 360)*DEG2RAD;
	bullet.firstShoot = true;
	bullet.setPosition(Vector2D(position.x+53/2, position.y +30/2));
	bullet.SetActive(true);
}

Vector2D Ovni::GetPosition()
{
	Vector2D centredPosition;
	centredPosition.x = position.x + 53 / 2;
	centredPosition.y = position.y + 30 / 2;
	return centredPosition;
}

void Ovni::UpdatePosition(float deltaTime)
{
	position.x += randomDirection.x*speed;
	position.y += randomDirection.y*speed;

	ovniSprite.transform.x = position.x;
	ovniSprite.transform.y = position.y;
}

void Ovni::Draw()
{
	ovniSprite.Draw();
	bullet.Draw();
}