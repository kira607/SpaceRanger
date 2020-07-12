//
// Created by Lad on 20.05.2020.
//

#include "input_box.h"

InputBox::InputBox(const sf::Font &font)
{
    input.setFont(font);
    input.setString("");
    input.setCharacterSize(30);
    input.setFillColor(colors::input_color);

    box.setSize(sf::Vector2f(constants::screen_width-10,40));
    box.setFillColor(colors::input_box_color);
    box.setOutlineThickness(1);
    box.setOutlineColor(sf::Color::White);
    Update();
}

void InputBox::setPosition(float x, float y)
{
    box.setPosition(x,y);
    Update();
}

void InputBox::setPosition(const sf::Vector2f &v)
{
    box.setPosition(v);
    Update();
}

float InputBox::width() const
{
    return box.getSize().x;
}

float InputBox::height() const
{
    return box.getSize().y;
}

void InputBox::AddChar(char ch)
{
    if(input.getString().getSize() < max_characters)
    {
        input.setString(input.getString() + ch);
    }
}

void InputBox::DeleteChar()
{
    if(!input.getString().isEmpty())
    {
        string new_string = input.getString();
        new_string.erase(new_string.end() - 1);
        input.setString(new_string);
    }
}

void InputBox::Update()
{
    input.setPosition(box.getPosition().x + box.getSize().x/2 - input.getGlobalBounds().width/2,
                      box.getPosition().y + box.getSize().y/2 - input.getGlobalBounds().height/2);
}

void InputBox::Draw(sf::RenderWindow &window) const
{
    window.draw(box);
    window.draw(input);
}
