//
// Created by Lad on 18.05.2020.
//

#include "main_menu.h"

MainMenu::MainMenu(const sf::Font& font, bool &music_on_arg, bool &sounds_on_arg):
        button_play(font, "PLAY"),
        button_controls(font, "CONTROLS"),
        button_exit(font, "EXIT"),
        button_leader_board(font, "LEADER BOARD"),
        button_music(font, "MUSIC"),
        button_sounds(font, "SOUNDS"),
        leader_board(font),
        music_on(music_on_arg),
        sounds_on(sounds_on_arg)
{
    controls_texture.loadFromFile("../pic/controls.png");
    controls.setTexture(controls_texture);
    controls.setPosition(-controls.getGlobalBounds().width-1,
                         0);
    controls.setScale(1,0.94);

    click_buffer.loadFromFile("../aud/click2.wav");
    click.setBuffer(click_buffer);

    status = MainMenuStatus::kMain;
    updating = false;
    sign = 1;

    front_flash.setSize(sf::Vector2f(constants::screen_width,constants::screen_height));
    front_flash.setPosition(0,0);
    front_flash.setFillColor(colors::flash_color);

    button_height = button_play.height();

    button_play.setPosition((constants::screen_width - button_play.width()) / 2,
                            constants::screen_height / 2 -
                            (button_height * 2 + space_between_buttons * 1.5));
    button_controls.setPosition((constants::screen_width - button_controls.width()) / 2,
                                constants::screen_height / 2 -
                                (button_height + space_between_buttons * 0.5));
    button_leader_board.setPosition((constants::screen_width - button_leader_board.width()) / 2,
                                    constants::screen_height / 2 + space_between_buttons * 0.5);
    button_exit.setPosition((constants::screen_width - button_exit.width()) / 2,
                            constants::screen_height / 2 + button_height + space_between_buttons * 1.5);
    button_music.setPosition(space_between_buttons,
                            constants::screen_height - button_music.height() - space_between_buttons);
    button_sounds.setPosition(constants::screen_width-space_between_buttons-button_sounds.width(),
            constants::screen_height - button_sounds.height() - space_between_buttons);

    leader_board.setPosition(constants::screen_width + leader_board.width() + 1,0);
    leader_board.Read();

    music.openFromFile("../mus/Sayer_Remembrance_Park.wav");
    music.setVolume(60);
}

void MainMenu::UpdateButtonsColors()
{
    if (MouseCursorIn(button_play.rectangle))
    {
        button_play.text.setFillColor(colors::text_play_color);
    }
    else
    {
        button_play.text.setFillColor(colors::text_color);
    }

    if (MouseCursorIn(button_exit.rectangle))
    {
        button_exit.text.setFillColor(colors::text_exit_color);
    }
    else
    {
        button_exit.text.setFillColor(colors::text_color);
    }

    if (MouseCursorIn(button_controls.rectangle))
    {
        button_controls.text.setFillColor(colors::text_controls_color);
    }
    else
    {
        button_controls.text.setFillColor(colors::text_color);
    }

    if (MouseCursorIn(button_leader_board.rectangle))
    {
        button_leader_board.text.setFillColor(colors::text_leader_board_color);
    }
    else
    {
        button_leader_board.text.setFillColor(colors::text_color);
    }

    if(music_on)
    {
        button_music.text.setFillColor(colors::on_color);
    }
    else
    {
        button_music.text.setFillColor(colors::off_color);
    }

    if(sounds_on)
    {
        button_sounds.text.setFillColor(colors::on_color);
    }
    else
    {
        button_sounds.text.setFillColor(colors::off_color);
    }
}

void MainMenu::Draw(sf::RenderWindow& window) const
{
    button_play.Draw(window);
    button_controls.Draw(window);
    button_exit.Draw(window);
    button_leader_board.Draw(window);
    button_music.Draw(window);
    button_sounds.Draw(window);
    leader_board.Draw(window);

    if(updating)
    {
        float t = updating_clock.getElapsedTime().asSeconds();
        int alpha = -1920 * t * t + 1020 * t;
        front_flash.setFillColor(sf::Color(255,255,255,alpha));
        if(alpha > 0)
        {
            window.draw(front_flash);
        }
        window.draw(controls);
        leader_board.Draw(window);
    }
    switch (status)
    {
        case MainMenuStatus::kMain:
            break;
        case MainMenuStatus::kControls:
            window.draw(controls);
            break;
        case MainMenuStatus::kLeaderBoard:
            leader_board.Draw(window);
            break;
    }

}

MainMenuSignal MainMenu::HandleClick()
{
    if(sounds_on)
    {
        click.play();
    }
    if(updating)
    {
        return MainMenuSignal::kNothing;
    }

    if(MouseCursorIn(button_play.rectangle))
    {
        music.stop();
        return MainMenuSignal::kStartGame;
    }
    if(MouseCursorIn(button_exit.rectangle))
    {
        return MainMenuSignal::kExitGame;
    }
    if(MouseCursorIn(button_controls.rectangle))
    {
        if(status == MainMenuStatus::kControls)
        {
            status = MainMenuStatus::kMain;
            updating_clock.restart();
            updating = true;
            sign = -1;
            return MainMenuSignal::kNothing;
        }
        else
        {
            status = MainMenuStatus::kControls;
            updating_clock.restart();
            updating = true;
            sign = 1;
            return MainMenuSignal::kNothing;
        }
    }
    if(MouseCursorIn(button_leader_board.rectangle))
    {
        if(status == MainMenuStatus::kLeaderBoard)
        {
            status = MainMenuStatus::kMain;
            updating_clock.restart();
            updating = true;
            sign = 1;
            return MainMenuSignal::kNothing;
        }
        else
        {
            status = MainMenuStatus::kLeaderBoard;
            updating_clock.restart();
            updating = true;
            sign = -1;
            return MainMenuSignal::kNothing;
        }
    }
    if(MouseCursorIn(button_music.rectangle))
    {
        return MainMenuSignal::kSwitchMusic;
    }
    if(MouseCursorIn(button_sounds.rectangle))
    {
        return MainMenuSignal::kSwitchSounds;
    }
    return MainMenuSignal::kNothing;
}

void MainMenu::Update()
{
    if(music_on)
    {
        if (music.getStatus() != sf::Music::Playing)
        {
            music.play();
        }
        if (music.getPlayingOffset().asSeconds() >=
            music.getDuration().asSeconds() - sf::seconds(1).asSeconds())
        {
            music.stop();
        }
    }
    else
    {
        music.stop();
    }

    UpdateButtonsColors();
    if(updating_clock.getElapsedTime() > sf::seconds(0.6))
    {
        updating = false;
    }
    switch (status)
    {
        case MainMenuStatus::kMain:
        {
            if (!updating)
            {
                break;
            }
            sf::Vector2f play_dest(constants::screen_width / 2 - button_play.width() / 2,
                                   button_play.getPosition().y);
            sf::Vector2f controls_dest(constants::screen_width / 2 - button_controls.width() / 2,
                                       button_controls.getPosition().y);
            sf::Vector2f leader_board_button_dest(constants::screen_width / 2 - button_leader_board.width() / 2,
                                                  button_leader_board.getPosition().y);
            sf::Vector2f exit_dest(constants::screen_width / 2 - button_exit.width() / 2,
                                   button_exit.getPosition().y);
            sf::Vector2f leader_board_dest(constants::screen_width+leader_board.width()+1,0);
            sf::Vector2f controls_sprite_dest(-controls.getGlobalBounds().width-1,0);
            MovePlayButtonToDest(play_dest);
            MoveControlsButtonToDest(controls_dest);
            MoveLeaderBoardButtonToDest(leader_board_button_dest);
            MoveExitButtonToDest(exit_dest);
            MoveControlsSpriteToDest(controls_sprite_dest);
            MoveLeaderBoardToDest(leader_board_dest);
        }
            break;
        case MainMenuStatus::kControls:
        {
            if (!updating)
            {
                break;
            }
            sf::Vector2f play_dest(constants::screen_width - space_between_buttons - button_play.width(),
                                   button_play.getPosition().y);
            sf::Vector2f controls_dest(constants::screen_width - space_between_buttons - button_controls.width(),
                                       button_controls.getPosition().y);
            sf::Vector2f leader_board_button_dest(
                    constants::screen_width - space_between_buttons - button_leader_board.width(),
                    button_leader_board.getPosition().y);
            sf::Vector2f exit_dest(constants::screen_width - space_between_buttons - button_exit.width(),
                                   button_exit.getPosition().y);
            sf::Vector2f leader_board_dest(constants::screen_width+leader_board.width()+1,0);
            sf::Vector2f controls_sprite_dest(0,0);
            MovePlayButtonToDest(play_dest);
            MoveControlsButtonToDest(controls_dest);
            MoveLeaderBoardButtonToDest(leader_board_button_dest);
            MoveExitButtonToDest(exit_dest);
            MoveControlsSpriteToDest(controls_sprite_dest);
            MoveLeaderBoardToDest(leader_board_dest);
        }
            break;
        case MainMenuStatus::kLeaderBoard:
        {
            if (!updating)
            {
                break;
            }
            sf::Vector2f play_dest(space_between_buttons, button_play.getPosition().y);
            sf::Vector2f controls_dest(space_between_buttons, button_controls.getPosition().y);
            sf::Vector2f leader_board_button_dest(space_between_buttons, button_leader_board.getPosition().y);
            sf::Vector2f exit_dest(space_between_buttons, button_exit.getPosition().y);
            sf::Vector2f controls_sprite_dest(-controls.getGlobalBounds().width-1,0);
            sf::Vector2f leader_board_dest(constants::screen_width-leader_board.width(),0);
            MovePlayButtonToDest(play_dest);
            MoveControlsButtonToDest(controls_dest);
            MoveLeaderBoardButtonToDest(leader_board_button_dest);
            MoveExitButtonToDest(exit_dest);
            MoveControlsSpriteToDest(controls_sprite_dest);
            MoveLeaderBoardToDest(leader_board_dest);

            leader_board.Read();
        }
            break;
    }
}

void MainMenu::MoveExitButtonToDest(const sf::Vector2f &dest)
{
    float path_length = sign * sqrt(
            (dest - button_exit.getPosition()).x * (dest - button_exit.getPosition()).x +
            (dest - button_exit.getPosition()).y * (dest - button_exit.getPosition()).y);
    button_exit.setPosition(
            button_exit.getPosition().x +
            path_length * updating_clock.getElapsedTime().asMilliseconds() / 1000,
            button_exit.getPosition().y);
}

void MainMenu::MovePlayButtonToDest(const sf::Vector2f &dest)
{
    float path_length = sign * sqrt(
            (dest - button_play.getPosition()).x * (dest - button_play.getPosition()).x +
            (dest - button_play.getPosition()).y * (dest - button_play.getPosition()).y);
    button_play.setPosition(
            button_play.getPosition().x +
            path_length * updating_clock.getElapsedTime().asMilliseconds() / 1000,
            button_play.getPosition().y);
}

void MainMenu::MoveControlsButtonToDest(const sf::Vector2f &dest)
{
    float path_length = sign * sqrt(
            (dest - button_controls.getPosition()).x *
            (dest - button_controls.getPosition()).x +
            (dest - button_controls.getPosition()).y *
            (dest - button_controls.getPosition()).y);
    button_controls.setPosition(
            button_controls.getPosition().x +
            path_length * updating_clock.getElapsedTime().asMilliseconds() / 1000,
            button_controls.getPosition().y);
}

void MainMenu::MoveLeaderBoardButtonToDest(const sf::Vector2f &dest)
{
    float path_length = sign * sqrt(
            (dest - button_leader_board.getPosition()).x *
            (dest - button_leader_board.getPosition()).x +
            (dest - button_leader_board.getPosition()).y *
            (dest - button_leader_board.getPosition()).y);
    button_leader_board.setPosition(
            button_leader_board.getPosition().x +
            path_length * updating_clock.getElapsedTime().asMilliseconds() / 1000,
            button_leader_board.getPosition().y);
}

void MainMenu::MoveControlsSpriteToDest(const sf::Vector2f &dest)
{
    float path_length = sign * sqrt(
            (dest - controls.getPosition()).x *
            (dest - controls.getPosition()).x +
            (dest - controls.getPosition()).y *
            (dest - controls.getPosition()).y);
    controls.setPosition(
            controls.getPosition().x +
            path_length * updating_clock.getElapsedTime().asMilliseconds() / 1000,
            controls.getPosition().y);
}

void MainMenu::MoveLeaderBoardToDest(const sf::Vector2f &dest)
{
    float path_length = sign * sqrt(
            (dest - leader_board.getPosition()).x *
            (dest - leader_board.getPosition()).x +
            (dest - leader_board.getPosition()).y *
            (dest - leader_board.getPosition()).y);
    leader_board.setPosition(
            leader_board.getPosition().x +
            path_length * updating_clock.getElapsedTime().asMilliseconds() / 1000,
            leader_board.getPosition().y);
}


