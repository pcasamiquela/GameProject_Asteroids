#include "Player.h"


Player::~Player()
{
//	delete[] bulletPool;
}

void Player::Update(float deltaTime)
{
	UpdateSpeed(deltaTime);
	UpdateAngle();
	DoWrap(position);
	UpdatePosition();
	if (canShoot) {
		if (IM.IsKeyDown<KEY_BUTTON_SPACE>() || IM.IsKeyDown<MOUSE_BUTTON_LEFT>()) {
			FireWeapon(bulletCounter);
			bulletCounter++;
			if (bulletCounter == MAX_BULLETS - 1) bulletCounter = 0;
		}
	}
	for (int i = 0; i < MAX_BULLETS; i++) {
		bulletPool[i].Update(deltaTime, playerSprite.angle*DEG2RAD);
		bulletPool[i].firstShoot = false;
	}
}


void Player::UpdateSpeed(float deltaTime) {

	if (IM.IsKeyHold<KEY_BUTTON_UP>() || IM.IsKeyHold<'w'>() && speedCounter <= MAX_SPEED) {
		speedCounter += (0.8f * deltaTime); 
		desiredVelocity.x = speedCounter*(sin(angle*DEG2RAD));
		desiredVelocity.y = speedCounter*(cos(angle*DEG2RAD));

	}
	if (IM.IsKeyDown<KEY_BUTTON_UP>() || IM.IsKeyHold<'w'>()) {
		previousVelocity = desiredVelocity;
		angle = playerSprite.angle;;
	}
	else {
		if (speedCounter > 0) speedCounter -= (0.4f*deltaTime);
	}
}

void Player::DoWrap(Vector2D& position){
	if (position.x > SCREEN_WIDTH + 25)
	{
		position.x = -25.0f;
	}
	else if (position.x < -25)
	{
		position.x = SCREEN_WIDTH + 25;
	}

	if (position.y > SCREEN_HEIGHT + 25)
	{
		position.y = -25.0f;
	}
	else if (position.y < -25)
	{
		position.y = SCREEN_HEIGHT + 25;
	}
}

void Player::UpdatePosition(){
	


	position.x += desiredVelocity.x;
	position.y -= desiredVelocity.y;


	playerSprite.transform.x = position.x;
	playerSprite.transform.y = position.y;
}

void Player::FireWeapon(int bullet)
{
	bulletPool[bullet].firstShoot = true;
	Vector2D circlePosition; //To know the direction of bullet, we make a circle and pick a point 
	circlePosition.x = position.x+width/2 + RADIUS*cos((playerSprite.angle-90)*DEG2RAD);
	circlePosition.y = position.y+height / 2 + RADIUS*sin((playerSprite.angle-90)*DEG2RAD);

	bulletPool[bullet].setPosition(circlePosition);
	bulletPool[bullet].SetActive(true);
	bulletPool[bulletCounter].lifeTime = 0;
}


void Player::UpdateAngle()
{
	mouseCoords = IM.GetMouseCoords();

	if (IM.IsKeyHold<KEY_BUTTON_LEFT>() || IM.IsKeyHold<'a'>()) playerSprite.angle -= 0.004f;
	if (IM.IsKeyHold<KEY_BUTTON_RIGHT>() || IM.IsKeyHold<'d'>()) playerSprite.angle += 0.004f;
	
	if (playerSprite.angle <= 0) playerSprite.angle = 360;
	else if (playerSprite.angle >= 360) playerSprite.angle = 0;
}


void Player::Draw()
{
	playerSprite.Draw();
	for (int i = 0; i < MAX_BULLETS; i++) {
		bulletPool[i].Draw();
	}
}

void Player::Reset()
{
	position.x = SCREEN_WIDTH / 2;
	position.y = SCREEN_HEIGHT / 2;
	speedCounter = 0;
}

Bullets& Player::GetCurrentBullet(int i)
{
	return bulletPool[i];
}

Vector2D Player::GetPosition()
{
	Vector2D centredPosition;
	centredPosition.x = position.x + width / 2;
	centredPosition.y = position.y + height / 2;
	return centredPosition;
}

