#include "Bullets.h"

Bullets::~Bullets()
{
}

void Bullets::Update(float deltaTime, float angle)
{
	if (isActive) {
		UpdatePosition(angle);
		DoWrap(position);
		lifeTime += deltaTime;	
		if (lifeTime >= 0.0075f) SetActive(false);
	}
}


void Bullets::UpdatePosition(float angle)
{
	
	if (firstShoot) {
		velocityDirection.x = MAX_SPEED*sin(angle);
		velocityDirection.y = MAX_SPEED*cos(angle);
	}
	position.x += velocityDirection.x;
	position.y -= velocityDirection.y;

	bulletSprite.transform.x = position.x;
	bulletSprite.transform.y = position.y;

}

void Bullets::DoWrap(Vector2D& position) {
	if (position.x > SCREEN_WIDTH)
	{
		position.x = 0.0f;
	}
	else if (position.x < 0)
	{
		position.x = SCREEN_WIDTH;
	}

	if (position.y > SCREEN_HEIGHT)
	{
		position.y = 0.0f;
	}
	else if (position.y < 0)
	{
		position.y = SCREEN_HEIGHT;
	}
}

void Bullets::Draw()
{
	if(isActive)bulletSprite.Draw();
}

void Bullets::SetActive(bool _isActive) {
	isActive = _isActive;
}

void Bullets::setPosition(Vector2D _position)
{
	position = _position;
}
