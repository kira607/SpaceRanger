//
// Created by Lad on 11.05.2020.
//

#include "shooter.h"

Shooter::Shooter(sf::Vector2f spaceship_pos, const sf::Texture& texture, const sf::Texture& light_texture)
{
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setScale(0.25f, 0.25f);

    // позиция генерации по краям экрана
    switch (Rand(0,3))
    {
        case 0: sprite.setPosition(0,Rand(0,constants::screen_height)); break;
        case 1: sprite.setPosition(constants::screen_width,Rand(0,constants::screen_height)); break;
        case 2: sprite.setPosition(Rand(0,constants::screen_width),0); break;
        case 3: sprite.setPosition(Rand(0,constants::screen_width),constants::screen_width); break;
    }

    hit_box.setRadius(sprite.getGlobalBounds().height * 0.45f);
    hit_box.setPointCount(30);
    hit_box.setFillColor(sf::Color(255,127,127,127));
    UpdateHitBoxPosition();

    dest_vector.x = 550;
    dest_vector.y = 0;

    float dX = spaceship_pos.x - sprite.getPosition().x;
    float dY = spaceship_pos.y - sprite.getPosition().y;
    float angle = atan2(dY, dX) * 180 / constants::pi;

    dest_vector = RotateVector(dest_vector,angle+90);
    dest_vector = RotateVector(dest_vector,Rand(0,180));

    shoot_light.setTexture(light_texture);
    shoot_light.setOrigin(shoot_light.getGlobalBounds().width/2, shoot_light.getGlobalBounds().height/2);
    shoot_light.setScale(1.1f,1.1f);
}

void Shooter::UpdateRotation(const sf::Sprite &spaceship)
{
    float dX = spaceship.getPosition().x - sprite.getPosition().x;
    float dY = spaceship.getPosition().y - sprite.getPosition().y;
    float angle = atan2(dY, dX) * 180 / constants::pi;
    sprite.setRotation(angle);
}

void Shooter::UpdateHitBoxPosition()
{
    hit_box.setPosition(sprite.getPosition().x-hit_box.getRadius(),sprite.getPosition().y-hit_box.getRadius());
}

void Shooter::Move(const sf::Sprite &spaceship)
{
    UpdateRotation(spaceship);
    dest_vector = RotateVector(dest_vector,0.5f);
    sf::Vector2f d_vector = dest_vector + spaceship.getPosition();
    mover = (d_vector - sprite.getPosition());
    float mover_length = sqrt(mover.x * mover.x + mover.y * mover.y);
    mover.x /= mover_length;
    mover.y /= mover_length;

    mover *= speed;
    //mover.x += x_offset;
    //mover.y += y_offset;

    sprite.setPosition(sprite.getPosition().x + mover.x, sprite.getPosition().y + mover.y);
    UpdateHitBoxPosition();
}

void Shooter::Shoot(const sf::Vector2f &spaceship_pos,
                    vector<ShooterBullet> &shooter_bullets, const sf::Texture& texture)
{
    shooter_bullets.emplace_back(this->sprite,spaceship_pos,texture);
    shoot_light_clock.restart();
}