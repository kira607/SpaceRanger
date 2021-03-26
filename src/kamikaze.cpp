//
// Created by Lad on 07.05.2020.
//

#include "kamikaze.h"

Kamikaze::Kamikaze(const sf::Texture& texture)
{
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setScale(0.12f, 0.1f);

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

    x_offset = Rand(-3,3);
    y_offset = Rand(-3,3);
}

void Kamikaze::UpdateRotation(const sf::Sprite &spaceship)
{
    float dX = spaceship.getPosition().x - sprite.getPosition().x;
    float dY = spaceship.getPosition().y - sprite.getPosition().y;
    float angle = atan2(dY, dX) * 180 / constants::pi;
    sprite.setRotation(angle);
}

void Kamikaze::UpdateHitBoxPosition()
{
    hit_box.setPosition(sprite.getPosition().x-hit_box.getRadius(),sprite.getPosition().y-hit_box.getRadius());
}

void Kamikaze::Move(const sf::Sprite &spaceship)
{
    UpdateRotation(spaceship);
    mover = (spaceship.getPosition() - sprite.getPosition());
    float mover_length = sqrt(mover.x * mover.x + mover.y * mover.y);
    mover.x /= mover_length;
    mover.y /= mover_length;

    if(mover_length > 100)
    {
        mover *= speed;
    }
    else
    {
        mover *= speed * 0.6f;
    }

    mover.x += x_offset;
    mover.y += y_offset;

    sprite.setPosition(sprite.getPosition().x + mover.x, sprite.getPosition().y + mover.y);
    UpdateHitBoxPosition();
}