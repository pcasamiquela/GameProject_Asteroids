#pragma once

struct Vector2D {
	float x = 0.0f;
	float y = 0.0f;

	Vector2D(float valueX = 0.0f, float valueY = 0.0f) : x{ valueX }, y{ valueY }
	{}

	inline Vector2D operator+(const Vector2D& v)
	{
		return Vector2D(x + v.x, y + v.y);
	}
	inline void operator+=(const Vector2D& v2)
	{
		x += v2.x;
		y += v2.y;
	}

	inline Vector2D operator-(const Vector2D& v)
	{
		return Vector2D(x - v.x, y - v.y);
	}
	inline void operator-=(const Vector2D& v)
	{
		x -= v.x;
		y -= v.y;
	}

	inline Vector2D operator*(float scalar)
	{
		return Vector2D(x * scalar, y * scalar);
	}
};