//
// Created by Lad on 14.05.2020.
//

#include "health_orb.h"

HealthPoint::HealthPoint(int hps, const sf::Vector2f& pos, const sf::Font& font, const sf::Texture& texture)
{
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setPosition(pos);

    hit_box.setRadius(sprite.getGlobalBounds().width / 2);
    hit_box.setPointCount(30);
    hit_box.setPosition(sprite.getPosition().x - hit_box.getRadius(), sprite.getPosition().y - hit_box.getRadius());
    hp = hps;

    text.setString(sf::String(std::to_string(hps)));
    text.setFont(font);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(30);
    text.setPosition(sprite.getPosition().x-text.getGlobalBounds().width/2,
                     sprite.getPosition().y-text.getGlobalBounds().height/2);
}
