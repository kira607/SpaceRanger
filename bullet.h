//
// Created by Lad on 07.05.2020.
//

#ifndef LCW_BULLET_H
#define LCW_BULLET_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "spaceship.h"

struct Spaceship;

struct Bullet
{
    Bullet(const Spaceship* spaceship, const sf::Sprite& scope, const sf::Texture& texture);

    void Move();
    void UpdateHitBoxPosition();
    sf::Sprite sprite;
    sf::CircleShape hit_box;
    float speed = 45.f;
    sf::Vector2f moving_vector;
    sf::Vector2f moving_vector_normalized;
    sf::Vector2f hit_box_vector;
};

#endif //LCW_BULLET_H
