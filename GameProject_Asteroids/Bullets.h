#pragma once
#include "System.h"
#include "Sprite.h"
#define MAX_SPEED 0.0075f
class Bullets
{
public:
	Bullets() {
		position = 0;
		bulletSprite = { { 0, 0, 8, 8 }, 0, ObjectID::BULLET };
		isActive = false;
		speedCounter = 0;
		lifeTime = 0;
		firstShoot = false;
	}
	Bullets(int x, int y, int width, int height){
		bulletSprite = { { x, y, width, height }, 0, ObjectID::BULLET };
		position.x = x;
		position.y = y;
		isActive = true;
		speedCounter = 0;
		lifeTime = 0;
	}

	~Bullets();
	void Update(float deltaTIme, float angle);
	void Draw();
	void SetActive(bool _isActive);
	void setPosition(Vector2D _position);
	float lifeTime;
	bool firstShoot;

private:
	Vector2D direction;
	Vector2D position;
	Vector2D velocityDirection;
	Sprite bulletSprite;
	bool isActive;
	float speedCounter;

	//reference to collisions!

	void UpdatePosition(float angle);
	void CheckCollisions();
	void DoWrap(Vector2D& position);
};

