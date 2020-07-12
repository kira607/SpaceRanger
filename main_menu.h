//
// Created by Lad on 18.05.2020.
//

#ifndef LCW_MAIN_MENU_H
#define LCW_MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>

#include "button.h"
#include "constants.h"
#include "mouse_cursor_in.h"
#include "main_menu_signal.h"
#include "leader_board.h"

enum class MainMenuStatus
{
    kMain,
    kControls,
    kLeaderBoard,
};

struct MainMenu
{
    MainMenu(const sf::Font& font, bool &music_on_arg, bool &sounds_on_arg);

    void Update();
    void UpdateButtonsColors();
    void Draw(sf::RenderWindow& window) const;

    MainMenuSignal HandleClick();

    void MoveExitButtonToDest(const sf::Vector2f& dest);
    void MovePlayButtonToDest(const sf::Vector2f& dest);
    void MoveControlsButtonToDest(const sf::Vector2f& dest);
    void MoveLeaderBoardButtonToDest(const sf::Vector2f& dest);
    void MoveControlsSpriteToDest(const sf::Vector2f& dest);
    void MoveLeaderBoardToDest(const sf::Vector2f& dest);

    static constexpr float space_between_buttons = 10.f;
    float button_height;

    mutable LeaderBoard leader_board;

    MainMenuStatus status;

    Button button_play;
    Button button_controls;
    Button button_exit;
    Button button_leader_board;
    Button button_music;
    Button button_sounds;

    sf::Clock updating_clock;
    bool updating;
    bool &music_on, &sounds_on;
    double sign;
    mutable sf::RectangleShape front_flash;

    sf::SoundBuffer click_buffer;
    sf::Sound click;
    sf::Music music;

    sf::Sprite controls;
    sf::Texture controls_texture;
};

#endif //LCW_MAIN_MENU_H
