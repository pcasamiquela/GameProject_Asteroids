#pragma once
#include "System.h"
#include "Sprite.h"
#include "Bullets.h"

class Ovni
{
public:
	Ovni();
	~Ovni();

	void Setup();
	void Update(float deltaTime);
	void Draw();
	float speed;
	Bullets bullet;
	Vector2D GetPosition();
	Vector2D playerPosition;
	void Shoot();
	int id;
private:
	Vector2D position;
	Vector2D randomDirection;
	Sprite ovniSprite;
	float bulletAngle;
	void DoWrap();
	void UpdatePosition(float deltaTime);
	void RandomizeDirection();
};

