#include "Player.h"


Player::~Player()
{
}

void Player::Update(float deltaTime)
{


	HandleInput();
	UpdateSpeed(deltaTime);
	UpdateAngle();
	if(IM.IsKeyHold<KEY_BUTTON_UP>() && speedCounter <= MAX_SPEED) speedCounter += (0.8f * deltaTime);
	else {
		if (speedCounter > 0) speedCounter -= (0.5f*deltaTime);
	}
	
	position.x += speedCounter*(sin(playerSprite.angle*DegToRad)*0.3f);

	position.y -= speedCounter*(cos(playerSprite.angle*DegToRad)*0.3f);


	if (IM.IsKeyHold<KEY_BUTTON_LEFT>()) playerSprite.angle -= 0.005f;
	if (IM.IsKeyHold<KEY_BUTTON_RIGHT>()) playerSprite.angle += 0.005f;
	if (playerSprite.angle <= 0) playerSprite.angle = 360;
	else if (playerSprite.angle >= 360) playerSprite.angle = 0;
	//std::cout << speedCounter*(sin(playerSprite.angle*DegToRad)) << std::endl;

//	playerSprite.angle = 90;

	DoWrap(position);


	playerSprite.transform.x = position.x;
	playerSprite.transform.y = position.y;
}

float Player::Sign(float x)
{
	if (x > 0.0f) return 1.0f;
	if (x < 0.0f) return -1.0f;
	return 0.0f;
}


float Player::ApplyFriction(float speed, float friction)
{
	return 0;
}

void Player::HandleInput()
{
	if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>())exit(0);
	// Keyboard movement
	Uint8 keyUp = IM.IsKeyDown<KEY_BUTTON_UP>();
	Uint8 keyDown = IM.IsKeyDown<KEY_BUTTON_DOWN>();
	Uint8 keyLeft = IM.IsKeyDown<KEY_BUTTON_LEFT>();;
	Uint8 keyRight = IM.IsKeyDown<KEY_BUTTON_RIGHT>();;

	// Update input flags
	moveHorizontal = keyRight - keyLeft;
	moveVertical = keyDown - keyUp;
}

void Player::UpdateSpeed(float deltaTime) {
}

void Player::DoWrap(Vector2D& position)
{
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


void Player::UpdateAngle()
{

}


void Player::Draw()
{
	playerSprite.Draw();
}

