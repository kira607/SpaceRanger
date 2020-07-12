//
// Created by Lad on 18.05.2020.
//

#include "mouse_cursor_in.h"

bool MouseCursorIn(const sf::RectangleShape& rect)
{
    return sf::Mouse::getPosition().x > rect.getPosition().x &&
           sf::Mouse::getPosition().x < rect.getPosition().x + rect.getSize().x
           && sf::Mouse::getPosition().y > rect.getPosition().y &&
           sf::Mouse::getPosition().y < rect.getPosition().y + rect.getSize().y;
}
