#pragma once
#include "math.h"
#include <cassert>
#include <iostream>

struct Vector2f
{
	float x = 0;
	float y = 0;

	Vector2f(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2f operator+(Vector2f v)
	{
		return Vector2f(x + v.x, y + v.y);
	}
	
	Vector2f operator-(Vector2f v)
	{
		return Vector2f(x - v.x, y - v.y);
	}

	Vector2f operator*(float n)
	{
		return Vector2f(x * n, y * n);
	}

	Vector2f operator/(float n)
	{
		assert(n);
		return Vector2f(x / n, y / n);
	}

	float operator*(Vector2f v)
	{
		return x * v.x + y * v.y;
	}

	float len()
	{
		return sqrt(x * x + y * y);
	}

	Vector2f normalize()
	{
		assert(this->len());
		float len = this->len();
		return Vector2f(x / len, y / len);
	}		
};
