#include "vector2fmath.h"
#include <iostream>
#include "Sphere.h"
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Springs");
	Sphere sphere1 = { {100, 100}, 20, {10, 0}, 1, 255, 0 ,0 };
	Sphere sphere2 = { {120, 100}, 20, {-10, 0}, 1, 0, 255 ,0 };
	sphere1.collideSpheres(&sphere2, &window);

	return(0);
}
