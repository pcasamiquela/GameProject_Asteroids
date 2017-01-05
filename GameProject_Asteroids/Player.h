#pragma once
#include "Sprite.h"
#include "System.h"
#include <math.h>
#include "Constants.h"
#include "Bullets.h"
#define MAX_SPEED 0.005f
#define RADIUS 25.0f
#define MAX_BULLETS 10
class Player
{

public:
	Player(Vector2D _position, int _width, int _height) : position(_position), width(_width), height(_height) {
		playerSprite = { { int(position.x), int(position.y), width, height }, 0, ObjectID::PLAYER };
		speedCounter = 0;
		bulletPool = new Bullets[MAX_BULLETS];
		bulletCounter = 0;
		canShoot = true;
	};
	~Player();
	void Update(float deltaTime);
	void Draw();
	Vector2D GetPosition();

private:
	int width, height;
	Vector2D position;
	float speedCounter;
	bool canShoot;

	Sprite playerSprite;
	Bullets* bulletPool;


	void UpdateSpeed(float deltaTime);
	void UpdateAngle();
	void DoWrap(Vector2D &position);
	void UpdatePosition();
	void FireWeapon(int bullet);
	int bulletCounter;
};

