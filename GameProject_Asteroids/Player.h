#pragma once
#include "Sprite.h"
#include "System.h"
#include <math.h>
#include "Constants.h"
#define MAX_SPEED 0.035f
#define DegToRad M_PI/180

class Player
{

public:
	Player(Vector2D _position, int _width, int _height) : position(_position), width(_width), height(_height) {
		playerSprite = { { int(position.x), int(position.y), width, height }, 0, ObjectID::PLAYER };
		speedCounter = 0;
	};
	~Player();
	void Update(float deltaTime);
	void Draw();

private:
	int x, y, width, height;
	Vector2D position;
	Vector2D speed;
	float speedCounter;

	Sprite playerSprite;

	int moveHorizontal;
	int moveVertical;
	float ApplyFriction(float speed, float friction);
	float Sign(float x);

	void HandleInput();
	void UpdateSpeed(float deltaTime);
	void UpdateAngle();
	void DoWrap(Vector2D &position);
};

