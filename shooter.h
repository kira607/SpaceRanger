//
// Created by Lad on 11.05.2020.
//

#ifndef LCW_SHOOTER_H
#define LCW_SHOOTER_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "constants.h"
#include "rand.h"
#include "rotate_vector.h"
#include "shooter_bullet.h"

struct Shooter
{
    explicit Shooter(sf::Vector2f spaceship_pos, const sf::Texture& texture, const sf::Texture& light_texture);
    void UpdateRotation(const sf::Sprite &spaceship);
    void UpdateHitBoxPosition();
    void Move(const sf::Sprite &spaceship);
    void Shoot(const sf::Vector2f &spaceship_pos,
               vector<ShooterBullet> &shooter_bullets, const sf::Texture& texture);

    sf::Vector2f mover;
    sf::Vector2f dest_vector;
    sf::Sprite sprite;
    sf::CircleShape hit_box;
    float speed = 6.f;
    sf::Clock shoot_clock;
    sf::Clock shoot_light_clock;
    sf::Sprite shoot_light;
};

#endif //LCW_SHOOTER_H
