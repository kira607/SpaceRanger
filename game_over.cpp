//
// Created by Lad on 20.05.2020.
//


#include "game_over.h"

GameOver::GameOver(const sf::Font &font, const int *score):
    input_box(font),
    button_exit(font,"EXIT"),
    button_ok(font,"OK")
{
    input_box.setPosition(constants::screen_width / 2 - input_box.width() / 2,
                          constants::screen_height / 2 - input_box.height() - space_between_buttons / 2);
    button_ok.setPosition(constants::screen_width / 2 + space_between_buttons / 2,
                          constants::screen_height / 2 + space_between_buttons / 2);
    button_exit.setPosition(constants::screen_width / 2 - button_exit.width() - space_between_buttons / 2,
                            constants::screen_height / 2 + space_between_buttons / 2);

    back.setSize(sf::Vector2f(constants::screen_width, constants::screen_height));
    back.setPosition(0, 0);
    back.setFillColor(sf::Color(0, 0, 0, 160));

    hint_text.setFont(font);
    hint_text.setString("PUT YOUR NAME HERE TO SAVE YOUR SCORE IN LEADER BOARD(" + to_string(*score) + "):");
    score_ptr = score;
    hint_text.setFillColor(sf::Color::White);
    hint_text.setCharacterSize(15);
    hint_text.setPosition(constants::screen_width / 2 - hint_text.getGlobalBounds().width / 2,
                               input_box.box.getPosition().y - hint_text.getGlobalBounds().height -
                               space_between_buttons);

    GAME_OVER_text.setFont(font);
    GAME_OVER_text.setString("GAME OVER");
    GAME_OVER_text.setFillColor(sf::Color::Red);
    GAME_OVER_text.setCharacterSize(100);
    GAME_OVER_text.setPosition(constants::screen_width / 2 - GAME_OVER_text.getGlobalBounds().width / 2,
                               hint_text.getPosition().y - GAME_OVER_text.getGlobalBounds().height -
                               space_between_buttons);
}

bool GameOver::HandleClick(int score) const
{
    if(MouseCursorIn(button_ok.rectangle))
    {
        if(input_box.input.getString().isEmpty())
        {
            return true;
        }
        else
        {
            WriteResult(score);
            return true;
        }
    }
    return MouseCursorIn(button_exit.rectangle);
}

void GameOver::WriteResult(int score) const
{
    ofstream fout;
    fout.open("../leader_board.txt",ios_base::app|ios_base::ate);
    if(!fout.is_open())
    {
        return;
    }
    fout << " " << input_box.input.getString().toAnsiString() << " " << score;
}

void GameOver::Update()
{
    hint_text.setString("PUT YOUR NAME HERE TO SAVE YOUR SCORE IN LEADER BOARD(" + to_string(*score_ptr) + "):");
    UpdateButtonsColors();
    input_box.Update();
}

void GameOver::UpdateButtonsColors()
{
    if(MouseCursorIn(button_ok.rectangle))
    {
        button_ok.text.setFillColor(colors::text_play_color);
    }
    else
    {
        button_ok.text.setFillColor(colors::text_color);
    }
    if(MouseCursorIn(button_exit.rectangle))
    {
        button_exit.text.setFillColor(colors::text_exit_color);
    }
    else
    {
        button_exit.text.setFillColor(colors::text_color);
    }
}

void GameOver::Draw(sf::RenderWindow &window) const
{
    window.draw(back);
    window.draw(GAME_OVER_text);
    window.draw(hint_text);
    button_ok.Draw(window);
    button_exit.Draw(window);
    input_box.Draw(window);
}


