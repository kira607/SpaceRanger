//
// Created by Lad on 13.05.2020.
//

#include "button.h"

Button::Button(const sf::Font& font, const sf::String& string)
{
    text.setCharacterSize(30);
    text.setString(string);
    text.setFont(font);
    text.setFillColor(colors::text_color);

    rectangle.setFillColor(colors::button_color);
    rectangle.setSize(sf::Vector2f(text.getGlobalBounds().width * 1.3f, text.getGlobalBounds().height * 1.6f));
    rectangle.setPosition(constants::screen_width / 2, constants::screen_height / 2);
    text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2,
                     rectangle.getPosition().y + rectangle.getSize().y / 2);
    text.setPosition(text.getPosition().x - text.getGlobalBounds().width / 2,
                     text.getPosition().y - text.getGlobalBounds().height / 2);

}

void Button::Draw(sf::RenderWindow &window) const
{
    window.draw(rectangle);
    window.draw(text);
}

void Button::setPosition(float x, float y)
{
    rectangle.setPosition(x, y);
    text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2,
                     rectangle.getPosition().y + rectangle.getSize().y / 2);
    text.setPosition(text.getPosition().x - text.getGlobalBounds().width / 2,
                     text.getPosition().y - text.getGlobalBounds().height / 2);
}

void Button::setPosition(sf::Vector2f v)
{
    rectangle.setPosition(v);
    text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2,
                     rectangle.getPosition().y + rectangle.getSize().y / 2);
    text.setPosition(text.getPosition().x - text.getGlobalBounds().width / 2,
                     text.getPosition().y - text.getGlobalBounds().height / 2);
}

float Button::width()
{
    return rectangle.getSize().x;
}

float Button::height()
{
    return rectangle.getSize().y;
}

const sf::Vector2f &Button::getPosition() const
{
    return rectangle.getPosition();
}
