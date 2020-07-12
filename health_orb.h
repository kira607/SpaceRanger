//
// Created by Lad on 14.05.2020.
//

#ifndef LCW_HEALTH_ORB_H
#define LCW_HEALTH_ORB_H

#include <SFML/Graphics.hpp>

struct HealthPoint
{
    HealthPoint(int hps, const sf::Vector2f& pos, const sf::Font& font, const sf::Texture& texture);
    sf::Sprite sprite;
    sf::CircleShape hit_box;
    int hp;
    sf::Text text;
};

#endif //LCW_HEALTH_ORB_H
