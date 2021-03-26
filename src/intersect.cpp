//
// Created by Lad on 26.05.2020.
//

#include "intersect.h"

bool Intersect(const sf::CircleShape& c1, const sf::CircleShape& c2)
{
    sf::Vector2f distance_vector = c1.getPosition() - c2.getPosition();
    float distance = sqrt(distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y);
    return c1.getRadius() + c2.getRadius() > distance;
}