//
// Created by Lad on 07.05.2020.
//

#ifndef LCW_SPACESHIP_H
#define LCW_SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <array>

#include "constants.h"
#include "colors.h"
#include "bullet.h"

struct Bullet;

using namespace std;

struct Spaceship
{
    Spaceship(const sf::Texture& texture, const sf::Texture& light_texture);
    void UpdateRotation(const sf::Sprite& scope);
    void UpdateHitBoxPosition();

    void Move(const sf::Sprite& scope);
    void MoveUp();
    void MoveLeft();
    void MoveDown();
    void MoveRight();

    void ReduceHealth(int health_to_reduce);
    void AddHealth(int health_to_add);
    void UpdateHealthBarColor();

    void Shoot(const sf::Sprite& scope, const sf::Texture& texture);

    void Draw(sf::RenderWindow& window);

    sf::Sprite sprite;
    sf::CircleShape hit_box;
    float speed = 10.f;

    bool alive;
    sf::RectangleShape health_point;
    sf::RectangleShape health_bar_frame;
    sf::RectangleShape health_bar;
    static constexpr float health_bar_max_size = 300;
    int health_points = 100;

    sf::Clock shoot_light_clock;
    sf::Sprite shoot_light;
    vector<Bullet> bullets;

};

#endif //LCW_SPACESHIP_H
