#include "Player.h"


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	UpdateSpeed(deltaTime);
	UpdateAngle();
	DoWrap(position);
	UpdatePosition();
	if (canShoot) {
		if (IM.IsKeyDown<KEY_BUTTON_SPACE>()) {
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
	if (IM.IsKeyHold<KEY_BUTTON_UP>() && speedCounter <= MAX_SPEED) speedCounter += (0.8f * deltaTime);
	else {
		if (speedCounter > 0) speedCounter -= (0.2f*deltaTime);
	}
}

void Player::DoWrap(Vector2D& position){
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

void Player::UpdatePosition(){
	
	position.x += speedCounter*(sin(playerSprite.angle*DEG2RAD));
	position.y -= speedCounter*(cos(playerSprite.angle*DEG2RAD));


	playerSprite.transform.x = position.x;
	playerSprite.transform.y = position.y;
}

void Player::FireWeapon(int bullet)
{
	bulletPool[bullet].firstShoot = true;
	Vector2D circlePosition; //To know the direction of bullet, we make a circle and pick a point 
	circlePosition.x = position.x+width/2 + RADIUS*cos((playerSprite.angle-90)*DEG2RAD);
	circlePosition.y = position.y+height / 2 + RADIUS*sin((playerSprite.angle-90)*DEG2RAD);

	Vector2D bulletDirection = circlePosition - position;
	bulletDirection.Normalize();
	bulletPool[bullet].setPosition(circlePosition);
	bulletPool[bullet].SetActive(true);
	bulletPool[bulletCounter].lifeTime = 0;
}


void Player::UpdateAngle()
{
	if (IM.IsKeyHold<KEY_BUTTON_LEFT>()) playerSprite.angle -= 0.002f;
	if (IM.IsKeyHold<KEY_BUTTON_RIGHT>()) playerSprite.angle += 0.002f;

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

Vector2D Player::GetPosition()
{
	return position;
}

