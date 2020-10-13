#include "vector2fmath.h"
#include <iostream>
#include "Sphere.h"
#include <SFML/Graphics.hpp>
#include "windows.h"

const float DT = 0.01;

void interaction_with_springs(Sphere* sphere1, Sphere* sphere2, Vector2f* spring)
{
	sphere1->acceleration = sphere1->acceleration + (sphere2->pos - sphere1->pos).normalize() * spring->x * ((sphere2->pos - sphere1->pos).len() - spring->y) / sphere1->m;
	sphere2->acceleration = sphere2->acceleration - (sphere2->pos - sphere1->pos).normalize() * spring->x * ((sphere2->pos - sphere1->pos).len() - spring->y) / sphere2->m;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Springs");
	const int N = 4;
	Sphere spheres[N];
	Vector2f springs[N][N];

	spheres[0] = Sphere({ 200, 200 }, { 0, 0 }, { 0, 0 }, 10, 10, 255, 0, 0);
	spheres[1] = Sphere({ 200, 600 }, { 0, 0 }, { 0, 0 }, 10, 10, 0, 255, 0);
	spheres[2] = Sphere({ 600, 200 }, { 0, 0 }, { 0, 0 }, 10, 10, 0, 0, 255);
	spheres[3] = Sphere({ 600, 600 }, { 0, 0 }, { 0, 0 }, 10, 1, 255, 128, 128);

	/*for (int i = 0; i < N; i++)
	{
		spheres[i] = Sphere({float(100 * (i + 1)), float(100 * (i + 1))}, {0, 0}, {0, 0}, 10, 10, 255, 0, 0);
	}*/

	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			springs[i][j] = { 2, 350 };
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
				if (springs[i][j].x != 0)
					(spheres[j].pos - spheres[i].pos).draw(spheres[i].pos, &window);
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
				interaction_with_springs(&spheres[i], &spheres[j], &springs[i][j]);
			}
		}
		for (int i = 0; i < N; i++)
		{
			spheres[i].move(DT);
			spheres[i].acceleration = Vector2f(0, 0);
		}
		Sleep(10);
	}
	return(0);
}
