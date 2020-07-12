//
// Created by Lad on 19.05.2020.
//

#ifndef LCW_PAUSE_MENU_H
#define LCW_PAUSE_MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include <cmath>
//#include <iostream>

#include "button.h"
#include "constants.h"
#include "mouse_cursor_in.h"
#include "pause_menu_signal.h"

struct PauseMenu
{
    explicit PauseMenu(const sf::Font& font, bool &sound_on_arg, bool &music_on_arg);

    void Update();
    void UpdateButtonsColors();
    void Draw(sf::RenderWindow& window) const;

    PauseMenuSignal HandleClick() const;

    static constexpr float space_between_buttons = 10.f;

    bool &sound_on;
    bool &music_on;

    Button button_exit;
    Button button_resume;
    Button button_music;
    Button button_sounds;

    sf::RectangleShape back;

    sf::SoundBuffer click_buffer;
    mutable sf::Sound click;
};

#endif //LCW_PAUSE_MENU_H
