//
// Created by Lad on 19.05.2020.
//

#include "pause_menu.h"

PauseMenu::PauseMenu(const sf::Font& font, bool &sound_on_arg, bool &music_on_arg):
        button_exit(font, "EXIT"),
        button_resume(font, "RESUME"),
        button_music(font, "MUSIC"),
        button_sounds(font, "SOUNDS"),
        music_on(music_on_arg),
        sound_on(sound_on_arg)
{
    back.setSize(sf::Vector2f(constants::screen_width,constants::screen_height));
    back.setPosition(0,0);
    back.setFillColor(sf::Color(0,0,0,130));

    click_buffer.loadFromFile("../rcs/aud/click2.wav");
    click.setBuffer(click_buffer);

    float button_height = button_resume.height();

    button_resume.setPosition((constants::screen_width - button_resume.width()) / 2,
                                constants::screen_height / 2 -
                                (button_height + space_between_buttons * 0.5));
    button_exit.setPosition((constants::screen_width - button_exit.width()) / 2,
                                    constants::screen_height / 2 + space_between_buttons * 0.5);

    button_music.setPosition(space_between_buttons,
                             constants::screen_height - button_music.height() - space_between_buttons);
    button_sounds.setPosition(constants::screen_width-space_between_buttons-button_sounds.width(),
                              constants::screen_height - button_sounds.height() - space_between_buttons);
}

void PauseMenu::Update()
{
    UpdateButtonsColors();
}

void PauseMenu::UpdateButtonsColors()
{
    if(MouseCursorIn(button_resume.rectangle))
    {
        button_resume.text.setFillColor(colors::text_play_color);
    }
    else
    {
        button_resume.text.setFillColor(colors::text_color);
    }
    if(MouseCursorIn(button_exit.rectangle))
    {
        button_exit.text.setFillColor(colors::text_exit_color);
    }
    else
    {
        button_exit.text.setFillColor(colors::text_color);
    }

    if(sound_on)
    {
        button_sounds.text.setFillColor(colors::on_color);
    }
    else
    {
        button_sounds.text.setFillColor(colors::off_color);
    }
    if(music_on)
    {
        button_music.text.setFillColor(colors::on_color);
    }
    else
    {
        button_music.text.setFillColor(colors::off_color);
    }
}

void PauseMenu::Draw(sf::RenderWindow &window) const
{
    window.draw(back);
    button_exit.Draw(window);
    button_resume.Draw(window);
    button_music.Draw(window);
    button_sounds.Draw(window);
}

PauseMenuSignal PauseMenu::HandleClick() const
{
    if(sound_on)
    {
        click.play();
    }
    if(MouseCursorIn(button_resume.rectangle))
    {
        return PauseMenuSignal::kReturn;
    }
    if(MouseCursorIn(button_exit.rectangle))
    {
        return PauseMenuSignal::kExit;
    }
    if(MouseCursorIn(button_sounds.rectangle))
    {
        return PauseMenuSignal::kSwitchSound;
    }
    if(MouseCursorIn(button_music.rectangle))
    {
        return PauseMenuSignal::kSwitchMusic;
    }
    return PauseMenuSignal::kNothing;
}
