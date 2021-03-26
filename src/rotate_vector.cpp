//
// Created by Lad on 13.05.2020.
//

#include "rotate_vector.h"

sf::Vector2f RotateVector(const sf::Vector2f& vec, float angle)
{
    angle = angle * constants::pi / 180;
    sf::Vector2f v;
    v.x = vec.x * cos(angle) - vec.y * sin(angle);
    v.y = vec.x * sin(angle) + vec.y * cos(angle);
    return v;
}