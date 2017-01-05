#pragma once
#include "Sprite.h"
#include "System.h"
#include <math.h>
#include "Constants.h"

class Asteroid
{
public:
	Asteroid();
	~Asteroid();

	void Update(float deltaTime);
	void Draw();
	void Setup();
	void ChangeSprite(ObjectID objectID, int newWidth, int newHight);
	Vector2D GetPosition();
	std::string asteroidState;
	int width, height;
	float speed;
	void RandomizeDirection();

private:
	Vector2D position;
	Vector2D randomDirection;
	Sprite asteroidSprite;
	void DoWrap(Vector2D &position);
	void UpdatePosition(float deltaTime);
};

