//
// Created by Lad on 19.05.2020.
//

#ifndef LCW_LEADER_BOARD_H
#define LCW_LEADER_BOARD_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>

#include "colors.h"
#include "constants.h"
#include "leader_board_line.h"

using namespace std;

struct LeaderBoard
{
    explicit LeaderBoard(const sf::Font& font);

    void Draw(sf::RenderWindow& window);

    float width() const;
    float height() const;
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& v);
    const sf::Vector2f &getPosition() const;
    void UpdateElementsPositions();
    void Read();

    //25 lines
    vector<LeaderBoardLine> lines;
    //LeaderBoardLine line;

    static constexpr float space_between_elements = 10;

    sf::Text label;
    sf::RectangleShape borders;
};

#endif //LCW_LEADER_BOARD_H
