//
// Created by Lad on 19.05.2020.
//

#include "leader_board_line.h"


LeaderBoardLine::LeaderBoardLine(const sf::Font &font)
{
    num.setString("0");
    num.setFont(font);
    num.setFillColor(sf::Color::Black);
    num.setCharacterSize(30);

    name.setString("-");
    name.setFont(font);
    name.setFillColor(sf::Color::Black);
    name.setCharacterSize(30);

    score.setString("-");
    score.setFont(font);
    score.setFillColor(sf::Color::Black);
    score.setCharacterSize(30);

    border.setSize(sf::Vector2f(constants::screen_width/2,40));
    border.setFillColor(sf::Color(0,0,0,0));
    border.setOutlineThickness(1);
    border.setOutlineColor(sf::Color::White);

    num_border.setSize(sf::Vector2f(border.getSize().x * 0.15f,40));
    num_border.setFillColor(sf::Color(0,0,0,0));
    num_border.setOutlineThickness(1);
    num_border.setOutlineColor(sf::Color::White);

    name_border.setSize(sf::Vector2f(border.getSize().x * 0.55f,40));
    name_border.setFillColor(sf::Color(0,0,0,0));
    name_border.setOutlineThickness(1);
    name_border.setOutlineColor(sf::Color::White);

    score_border.setSize(sf::Vector2f(border.getSize().x * 0.30f,40));
    score_border.setFillColor(sf::Color(0,0,0,0));
    score_border.setOutlineThickness(1);
    score_border.setOutlineColor(sf::Color::White);

    UpdateElementsPositions();
}

float LeaderBoardLine::width() const
{
    return border.getSize().x;
}

float LeaderBoardLine::height() const
{
    return border.getSize().y;
}

void LeaderBoardLine::setPosition(float x, float y)
{
    border.setPosition(x,y);
    UpdateElementsPositions();
}

void LeaderBoardLine::setPosition(const sf::Vector2f &v)
{
    border.setPosition(v);
    UpdateElementsPositions();
}

const sf::Vector2f &LeaderBoardLine::getPosition() const
{
    return border.getPosition();
}

void LeaderBoardLine::UpdateElementsPositions()
{
    num_border.setPosition(border.getPosition());
    num.setPosition(num_border.getPosition().x + num_border.getSize().x / 2 - num.getGlobalBounds().width / 2,
                    num_border.getPosition().y+ num_border.getSize().y / 2 - num.getGlobalBounds().height / 2);

    name_border.setPosition(num_border.getPosition().x + num_border.getSize().x, border.getPosition().y);
    name.setPosition(name_border.getPosition().x + name_border.getSize().x / 2 - name.getGlobalBounds().width / 2,
                     name_border.getPosition().y + name_border.getSize().y / 2 - name.getGlobalBounds().height / 2);

    score_border.setPosition(name_border.getPosition().x + name_border.getSize().x, border.getPosition().y);
    score.setPosition(score_border.getPosition().x + score_border.getSize().x / 2 - score.getGlobalBounds().width / 2,
                      score_border.getPosition().y + score_border.getSize().y / 2 - score.getGlobalBounds().height / 2);
}

void LeaderBoardLine::Draw(sf::RenderWindow& window)
{
    window.draw(border);
    window.draw(num_border);
    window.draw(name_border);
    window.draw(score_border);
    window.draw(num);
    window.draw(name);
    window.draw(score);
}

void LeaderBoardLine::SetFields(int num_s, string n_s, string score_s)
{
    num.setString(to_string(num_s));
    name.setString(n_s);
    score.setString(score_s);
}


