//
// Created by Lad on 13.05.2020.
//

#ifndef LCW_SHOOTER_BULLET_H
#define LCW_SHOOTER_BULLET_H

#include <SFML/Graphics.hpp>
#include <cmath>

struct ShooterBullet
{
    ShooterBullet(const sf::Sprite& shooter, const sf::Vector2f& spaceship_pos, const sf::Texture& texture);
    void Move();
    void UpdateHitBoxPosition();
    sf::Sprite sprite;
    sf::CircleShape hit_box;
    float speed = 30.f;
    sf::Vector2f moving_vector;
    sf::Vector2f moving_vector_normalized;
    sf::Vector2f hit_box_vector;
};

#endif //LCW_SHOOTER_BULLET_H
