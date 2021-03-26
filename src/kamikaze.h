//
// Created by Lad on 07.05.2020.
//

#ifndef LCW_KAMIKAZE_H
#define LCW_KAMIKAZE_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "constants.h"
#include "rand.h"

struct Kamikaze
{
    explicit Kamikaze(const sf::Texture& texture);
    void UpdateRotation(const sf::Sprite& spaceship);
    void UpdateHitBoxPosition();
    void Move(const sf::Sprite &spaceship);
    sf::Vector2f mover;
    float x_offset;
    float y_offset;
    sf::Sprite sprite;
    sf::CircleShape hit_box;
    float speed = 8.f;
};

#endif //LCW_KAMIKAZE_H
