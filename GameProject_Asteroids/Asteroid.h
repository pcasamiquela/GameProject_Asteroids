#pragma once
#include "Sprite.h"
#include "System.h"
#include <math.h>
#include "Constants.h"

#define SPEED 0.0005f;

class Asteroid
{
public:
	Asteroid();
	~Asteroid();

	void Update(float deltaTime);
	void Draw();
	void Setup();
private:
	Vector2D position;
	Vector2D randomDirection;
	Sprite asteroidSprite;

	void DoWrap(Vector2D &position);
	void UpdatePosition(float deltaTime);
};

