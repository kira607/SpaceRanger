//
// Created by Lad on 20.05.2020.
//

#ifndef LCW_INPUT_BOX_H
#define LCW_INPUT_BOX_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "constants.h"
#include "colors.h"

using namespace std;

struct InputBox
{
    explicit InputBox(const sf::Font &font);

    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f &v);
    float width() const;
    float height() const;
    void AddChar(char ch);
    void DeleteChar();
    void Update();

    void Draw(sf::RenderWindow &window) const;

    sf::RectangleShape box;
    sf::Text input;
    const int max_characters = 20;
};

#endif //LCW_INPUT_BOX_H
