//
// Created by Lad on 20.05.2020.
//

#ifndef LCW_GAME_OVER_H
#define LCW_GAME_OVER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

#include "button.h"
#include "constants.h"
#include "mouse_cursor_in.h"
#include "input_box.h"

using namespace std;

struct GameOver
{
    explicit GameOver(const sf::Font &font, const int *score);

    void Update();
    void UpdateButtonsColors();
    void Draw(sf::RenderWindow& window) const;

    bool HandleClick(int score) const;
    void WriteResult(int score) const;

    const int *score_ptr;

    static constexpr float space_between_buttons = 10.f;

    Button button_exit;
    Button button_ok;
    InputBox input_box;

    sf::Text GAME_OVER_text, hint_text;

    sf::RectangleShape back;
};

#endif //LCW_GAME_OVER_H
