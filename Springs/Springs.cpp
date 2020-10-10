#include "vector2fmath.h"
#include <iostream>

int main()
{
	Vector2f v1(3, 4);
	Vector2f v2(5, -3);
	std::cout << v1 * v2 << " " << v1 * v2;
	return(0);
}