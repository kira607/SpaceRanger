//
// Created by Lad on 19.05.2020.
//

#include "leader_board.h"

#include <utility>

LeaderBoard::LeaderBoard(const sf::Font &font)
    //line(font)
{
    label.setFont(font);
    label.setString("LEADER BOARD");
    label.setFillColor(sf::Color::Black);
    label.setCharacterSize(30);

    borders.setSize(sf::Vector2f(constants::screen_width / 2, constants::screen_height - 70));
    borders.setFillColor(sf::Color(0, 0, 0, 0));
    borders.setOutlineThickness(1);
    borders.setOutlineColor(sf::Color::White);

    for(int i = 0; i < 23; ++i)
    {
        lines.emplace_back(font);
        auto it = lines.end()-1;
        it->setPosition(borders.getPosition().x,
                        label.getPosition().y + label.getGlobalBounds().height + space_between_elements + i*it->height());
    }

    UpdateElementsPositions();
}

float LeaderBoard::width() const
{
    return borders.getSize().x;
}

float LeaderBoard::height() const
{
    return borders.getSize().y;
}

void LeaderBoard::setPosition(float x, float y)
{
    borders.setPosition(x,y);
    UpdateElementsPositions();
}

void LeaderBoard::setPosition(const sf::Vector2f& v)
{
    borders.setPosition(v);
    UpdateElementsPositions();
}

void LeaderBoard::UpdateElementsPositions()
{
    int i = 0;
    for(auto& line : lines)
    {
        line.setPosition(borders.getPosition().x,
                        label.getPosition().y + label.getGlobalBounds().height + space_between_elements + i*line.height());
        ++i;
    }

    //line.setPosition(borders.getPosition().x,label.getPosition().y + label.getGlobalBounds().height + space_between_elements);

    label.setPosition(borders.getPosition().x + borders.getSize().x/2 - label.getGlobalBounds().width/2,
                      borders.getPosition().y + label.getGlobalBounds().height + space_between_elements);
}

void LeaderBoard::Draw(sf::RenderWindow& window)
{
    window.draw(label);
    window.draw(borders);
    for(auto& line : lines)
    {
        line.Draw(window);
    }
}

const sf::Vector2f &LeaderBoard::getPosition() const
{
    return borders.getPosition();
}

void LeaderBoard::Read()
{
    ifstream fin("../leader_board.txt");
    if(!fin.is_open())
    {
        return;
    }

    struct Player
    {
        Player(string n, int s)
        {
            name = std::move(n);
            score = s;
        }
        string name;
        int score;
    };

    vector<Player> players;

    string name, score;
    while(!fin.eof())
    {
        fin >> name >> score;
        try
        {
            players.emplace_back(name, stoi(score));
        }
        catch (exception&)
        {
            break;
        }
    }

    std::sort(players.begin(),players.end(),[](const Player& p1, const Player& p2){
        return p1.score > p2.score;
    });

    int i = 1;
    auto it = players.begin();
    for(auto& line : lines)
    {
        if(it != players.end())
        {
            line.SetFields(i,it->name,to_string(it->score));
            ++it;
        }
        else
        {
            line.SetFields(i,"","");
        }
        ++i;
    }
}
