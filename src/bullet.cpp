//
// Created by Lad on 07.05.2020.
//

#include "bullet.h"

Bullet::Bullet(const Spaceship* spaceship, const sf::Sprite& scope, const sf::Texture& texture)
{
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setScale(0.05f, 0.05f);
    sprite.setPosition(spaceship->sprite.getPosition().x,spaceship->sprite.getPosition().y);
    float width = sprite.getGlobalBounds().width;

    hit_box.setRadius(sprite.getGlobalBounds().height * 0.6f);
    hit_box.setPointCount(30);
    hit_box.setFillColor(sf::Color(255,0,0,127));

    sprite.setRotation(spaceship->sprite.getRotation());

    sf::Vector2f scope_vector(scope.getPosition());
    sf::Vector2f spaceship_vector(spaceship->sprite.getPosition());
    moving_vector = scope_vector - spaceship_vector;
    float moving_vector_length = sqrt(moving_vector.x * moving_vector.x + moving_vector.y * moving_vector.y);
    moving_vector.x /= moving_vector_length;
    moving_vector.y /= moving_vector_length;
    moving_vector_normalized = moving_vector;
    moving_vector *= speed;

    hit_box_vector = (moving_vector_normalized * (width/2)) * 0.6f;
    UpdateHitBoxPosition();
}

void Bullet::Move()
{
    sprite.setPosition(sprite.getPosition().x + moving_vector.x, sprite.getPosition().y + moving_vector.y);
    UpdateHitBoxPosition();
}

void Bullet::UpdateHitBoxPosition()
{
    hit_box.setPosition(sprite.getPosition().x + hit_box_vector.x - hit_box.getRadius(),sprite.getPosition().y + hit_box_vector.y - hit_box.getRadius());
}
