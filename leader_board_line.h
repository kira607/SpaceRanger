//
// Created by Lad on 19.05.2020.
//

#ifndef LCW_LEADER_BOARD_LINE_H
#define LCW_LEADER_BOARD_LINE_H

#include <SFML/Graphics.hpp>
#include <string>

#include "constants.h"

using namespace std;

struct LeaderBoardLine
{
    explicit LeaderBoardLine(const sf::Font& font);

    float width() const;
    float height() const;
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& v);
    const sf::Vector2f &getPosition() const;

    void SetFields(int num, string n, string score);
    void UpdateElementsPositions();
    void Draw(sf::RenderWindow& window);

    sf::Text num,name,score;
    sf::RectangleShape border, num_border, name_border, score_border;
};

#endif //LCW_LEADER_BOARD_LINE_H
