//
// Created by Lad on 13.05.2020.
//

#ifndef LCW_BUTTON_H
#define LCW_BUTTON_H

#include <SFML/Graphics.hpp>

#include "constants.h"
#include "colors.h"

struct Button
{
    Button(const sf::Font& font, const sf::String& string = "BUTTON");

    void Draw(sf::RenderWindow& window) const;

    void setPosition(float x, float y);
    void setPosition(sf::Vector2f v);
    const sf::Vector2f& getPosition() const;
    float width();
    float height();

    sf::Text text;
    sf::RectangleShape rectangle;
};

#endif //LCW_BUTTON_H
