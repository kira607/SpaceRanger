//
// Created by Lad on 26.05.2020.
//

#include "inside_window.h"

bool InsideWindow(const sf::Sprite& s)
{
    return s.getPosition().x > 0 && s.getPosition().x < constants::screen_width &&
           s.getPosition().y > 0 && s.getPosition().y < constants::screen_height;
}
