#include "vector2fmath.h"
#include <iostream>
#include "Sphere.h"
#include <SFML/Graphics.hpp>
#include "windows.h"

const float DT = 0.01;

struct Spring
{
	float rate;
	float len;

	void draw(Vector2f pos1, Vector2f pos2, sf::RenderWindow* window)
	{
		sf::RectangleShape line(sf::Vector2f((pos2 - pos1).len(), 2));
		line.setFillColor(sf::Color(255, 255, 0));
		if (pos2.x - pos1.x >= 0)
		{
			line.setPosition(pos1.x, pos1.y);
			line.setRotation(180 / M_PI * atan((pos2.y - pos1.y) / (pos2.x - pos1.x)));
		}
		else
		{
			line.setPosition(pos2.x, pos2.y);
			line.setRotation(180 / M_PI * atan((pos2.y - pos1.y) / (pos2.x - pos1.x)));
		}
		window->draw(line);
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Springs");

	const int N = 4;
	Sphere spheres[N];
	Spring springs[N][N];

	spheres[0] = Sphere({ 200, 200 }, { 0, 0 }, { 0, 0 }, 10, 10, 255, 0, 0);
	spheres[1] = Sphere({ 200, 600 }, { 0, 0 }, { 0, 0 }, 10, 10, 0, 255, 0);
	spheres[2] = Sphere({ 600, 200 }, { 0, 0 }, { 0, 0 }, 10, 10, 0, 0, 255);
	spheres[3] = Sphere({ 600, 600 }, { 0, 0 }, { 0, 0 }, 10, 10, 255, 128, 128);

	/*for (int i = 0; i < N; i++)
	{
		spheres[i] = Sphere({float(100 * (i + 1)), float(100 * (i + 1))}, {0, 0}, {0, 0}, 10, 10, 255, 0, 0);
	}*/

	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			springs[i][j] = { 0.1, 350 };
		}
	}

	while (window.isOpen())
	{
		sf::Event event;

		window.clear();
		for (int i = 0; i < N; i++)
		{
			spheres[i].draw(&window);
			for (int j = i + 1; j < N; j++)
			{
				if (springs[i][j].rate != 0)
					springs[i][j].draw(spheres[i].pos, spheres[j].pos, &window);
			}
		}
		window.display();

		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (event.key.code == sf::Keyboard::Escape))
			{
				window.close();
				break;
			}
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = i + 1; j < N; j++)
			{
				spheres[i].acceleration = spheres[i].acceleration + (spheres[j].pos - spheres[i].pos).normalize() * springs[i][j].rate * ((spheres[j].pos - spheres[i].pos).len() - springs[i][j].len) / spheres[i].m;
				spheres[j].acceleration = spheres[j].acceleration - (spheres[j].pos - spheres[i].pos).normalize() * springs[i][j].rate * ((spheres[j].pos - spheres[i].pos).len() - springs[i][j].len) / spheres[j].m;
			}
		}

		for (int i = 0; i < N; i++)
		{
			spheres[i].move(DT);
			spheres[i].acceleration = Vector2f(0, 0);
		}
	}
	return(0);
}
