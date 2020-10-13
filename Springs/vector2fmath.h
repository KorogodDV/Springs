#pragma once
#define _USE_MATH_DEFINES
#include "math.h"
#include <cassert>
#include <iostream>
#include <SFML/Graphics.hpp>

struct Vector2f
{
	float x = 0;
	float y = 0;

	Vector2f(float x = 0, float y = 0)
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
	void draw(Vector2f pos, sf::RenderWindow* window)
	{
		sf::RectangleShape line(sf::Vector2f(this->len(), 2));
		line.setFillColor(sf::Color(255, 255, 0));
		if (x >= 0)
		{
			line.setPosition(pos.x, pos.y);
			line.setRotation(180 / M_PI * atan(y / x));
		}
		else
		{
			line.setPosition((pos + *this).x, (pos + *this).y);
			line.setRotation(180 / M_PI * atan(y / x));
		}
		window->draw(line);
	}
};
