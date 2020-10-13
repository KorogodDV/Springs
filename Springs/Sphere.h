#pragma once
#include "math.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include "vector2fmath.h"

struct Sphere
{
    Vector2f pos;
    Vector2f speed;
    Vector2f acceleration;
    float r;
    float m;
    int red;
    int green;
    int blue;

    Sphere(Vector2f pos = Vector2f(0, 0), Vector2f speed = Vector2f(0, 0), Vector2f acceleration = Vector2f(0, 0), float r = 0, float m = 1, int red = 0, int green = 0, int blue = 0)
    {
        this->pos = pos;
        this->speed = speed;
        this->acceleration = acceleration;
        this->r = r;
        this->m = m;
        this->red = red;
        this->green = green;
        this->blue = blue;
    }

    void draw(sf::RenderWindow* window, int lighting_detailing = 10)
    {
        float window_length = window->getSize().x;
        float window_width = window->getSize().y;
        assert((pos.x > r) & (pos.x + r < window_length) & (pos.y > r) & (pos.y + r < window_width));
        sf::CircleShape circle(r, 10);
        for (int i = 0; i < lighting_detailing; i++)
        {
            circle.setRadius(r - r * i / lighting_detailing);
            circle.setPosition(pos.x - r + 1.4 * r * i / lighting_detailing, pos.y - r + 0.6 * r * i / lighting_detailing);
            circle.setFillColor(sf::Color(0.875 * red * i / lighting_detailing + 0.125 * red, 0.875 * green * i / lighting_detailing + 0.125 * green, 0.875 * blue * i / lighting_detailing + 0.125 * blue));
            window->draw(circle);
        }
    }

    void move(const float DT)
    {
        speed = speed + acceleration * DT;
        pos = pos + speed * DT;
    }


    void checkColideWithWalls(float DT, sf::RenderWindow* window)
    {
        float window_length = window->getSize().x;
        float window_width = window->getSize().y;
        if (pos.x + speed.x * DT + r > window_length)
        {
            speed.x *= -1;
            pos.x = 2 * window_length - pos.x - 2 * r;
        }
        if (pos.x + speed.x * DT - r < 0)
        {
            speed.x *= -1;
            pos.x = -pos.x + 2 * r;
        }
        if (pos.y + speed.y * DT + r > window_width)
        {
            speed.y *= -1;
            pos.y = 2 * window_width - pos.y - 2 * r;
        }
        if (pos.y + speed.y * DT - r < 0)
        {
            speed.y *= -1;
            pos.y = -pos.y + 2 * r;
        }
    }

    bool checkCollisionTwoSpheres(Sphere* sphere2)
    {
        return pow(pos.x - sphere2->pos.x, 2) + pow(pos.y - sphere2->pos.y, 2) < pow(r + sphere2->r, 2);
    }

    void collideSpheres(Sphere* sphere2, sf::RenderWindow* window)
    {
        float window_length = window->getSize().x;
        float window_width = window->getSize().y;
        float vx10 = speed.x;
        float vy10 = speed.y;
        float vx20 = sphere2->speed.x;
        float vy20 = sphere2->speed.y;
        float dist = sqrt(pow(sphere2->pos.x - pos.x, 2) + pow(sphere2->pos.y - pos.y, 2));
        float dist_x = sphere2->pos.x - pos.x;
        float dist_y = sphere2->pos.y - pos.y;
        assert(dist);

        if ((pos.x - (r + sphere2->r - dist) * dist_x / (2 * dist) > r) & (pos.x - (r + sphere2->r - dist) * dist_x / (2 * dist) < window_length - r) & (sphere2->pos.x + (r + sphere2->r - dist) * dist_x / (2 * dist) > sphere2->r) & (sphere2->pos.x + (r + sphere2->r - dist) * dist_x / (2 * dist) < window_length - sphere2->r))
        {
            pos.x -= (r + sphere2->r - dist) * dist_x / (2 * dist);
            sphere2->pos.x += (r + sphere2->r - dist) * dist_x / (2 * dist);
        }
        else if ((pos.x - (r + sphere2->r - dist) * dist_x / (2 * dist)) <= r)
            sphere2->pos.x += (r + sphere2->r - dist) * dist_x / dist;
        else if ((pos.x - (r + sphere2->r - dist) * dist_x / (2 * dist)) >= window_length - r)
            sphere2->pos.x += (r + sphere2->r - dist) * dist_x / dist;
        else if ((sphere2->pos.x + (r + sphere2->r - dist) * dist_x / (2 * dist)) <= sphere2->r)
            pos.x -= (r + sphere2->r - dist) * dist_x / dist;
        else
            pos.x -= (r + sphere2->r - dist) * dist_x / dist;

        if ((pos.y - (r + sphere2->r - dist) * dist_y / (2 * dist) > r) & (pos.y - (r + sphere2->r - dist) * dist_y / (2 * dist) < window_length - r) & (sphere2->pos.y + (r + sphere2->r - dist) * dist_y / (2 * dist) > sphere2->r) & (sphere2->pos.y + (r + sphere2->r - dist) * dist_y / (2 * dist) < window_length - sphere2->r))
        {
            pos.y -= (r + sphere2->r - dist) * dist_y / (2 * dist);
            sphere2->pos.y += (r + sphere2->r - dist) * dist_y / (2 * dist);
        }
        else if ((pos.y - (r + sphere2->r - dist) * dist_y / (2 * dist)) <= r)
            sphere2->pos.y += (r + sphere2->r - dist) * dist_y / dist;
        else if ((pos.y - (r + sphere2->r - dist) * dist_y / (2 * dist)) >= window_width - r)
            sphere2->pos.y += (r + sphere2->r - dist) * dist_y / dist;
        else if ((sphere2->pos.y + (r + sphere2->r - dist) * dist_y / (2 * dist)) <= sphere2->r)
            pos.y -= (r + sphere2->r - dist) * dist_y / dist;
        else
            pos.y -= (r + sphere2->r - dist) * dist_y / dist;

        speed.x = (2 * sphere2->m * vx20 + (m - sphere2->m) * vx10) / (m + sphere2->m);
        speed.y = (2 * sphere2->m * vy20 + (m - sphere2->m) * vy10) / (m + sphere2->m);
        sphere2->speed.x = (2 * m * vx10 + (sphere2->m - m) * vx20) / (m + sphere2->m);
        sphere2->speed.y = (2 * m * vy10 + (sphere2->m - m) * vy20) / (m + sphere2->m);
    }
};


