#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "spaceship.h"
#include "kamikaze.h"
#include "constants.h"
#include "shooter.h"
#include "button.h"
#include "colors.h"
#include "health_orb.h"
#include "main_menu.h"
#include "game_status.h"
#include "pause_menu.h"
#include "game_over.h"
#include "inside_window.h"
#include "intersect.h"

using namespace std;

int main()
{
    // окно

    sf::RenderWindow window(sf::VideoMode(constants::screen_width,constants::screen_height), "Space Ranger",sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(true);
    window.setMouseCursorVisible(false);

    bool play_music = true;
    bool play_sounds = true;

    //текстуры

    sf::Texture scope_texture;
    sf::Texture background_texture;
    sf::Texture bullet_texture;
    sf::Texture spaceship_texture;
    sf::Texture kamikaze_texture;
    sf::Texture shooter_texture;
    sf::Texture shooter_bullet_texture;
    sf::Texture cursor_texture;
    sf::Texture health_orb_texture;
    sf::Texture shoot_light_texture;
    sf::Texture shooter_light_texture;

    std::string rcs = "../rcs/";

    if(!scope_texture.loadFromFile(rcs + "pic/ms2.png")) return -1;
    if(!background_texture.loadFromFile(rcs + "pic/background.jpg")) return -1;
    if(!bullet_texture.loadFromFile(rcs + "pic/bullet.png")) return -1;
    if(!spaceship_texture.loadFromFile(rcs + "pic/spaceship.png")) return -1;
    if(!kamikaze_texture.loadFromFile(rcs + "pic/kamikaze.png")) return -1;
    if(!shooter_texture.loadFromFile(rcs + "pic/shooter.png")) return -1;
    if(!shooter_bullet_texture.loadFromFile(rcs + "pic/shooter_bullet.png")) return -1;
    if(!cursor_texture.loadFromFile(rcs + "pic/cursor.png")) return -1;
    if(!health_orb_texture.loadFromFile(rcs + "pic/health_orb.png")) return -1;
    if(!shoot_light_texture.loadFromFile(rcs + "pic/particle_shoot.png")) return -1;
    if(!shooter_light_texture.loadFromFile(rcs + "pic/particle_shoot_shooter.png")) return -1;

    //шрифты

    sf::Font font_mk_90;
    font_mk_90.loadFromFile(rcs + "fonts/MK-90.ttf");

    //Button b(font_mk_90);
    //cout << b.text.getCharacterSize();

    //серый задник

    sf::RectangleShape back;
    back.setSize(sf::Vector2f(constants::screen_width, constants::screen_height));
    back.setFillColor(colors::back_color);

    //космос

    sf::Sprite background(background_texture);

    //прицел

    sf::Sprite scope(scope_texture);
    scope.setOrigin(scope.getGlobalBounds().width/2,scope.getGlobalBounds().height/2);
    scope.setPosition(sf::Mouse::getPosition().x - scope.getGlobalBounds().width / 2,
                      sf::Mouse::getPosition().y - scope.getGlobalBounds().height / 2);

    //курсор

    sf::Sprite cursor(cursor_texture);
    cursor.setScale(0.05f,0.05f);
    cursor.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

    //корабль

    Spaceship spaceship(spaceship_texture,shoot_light_texture);
    spaceship.UpdateRotation(scope);

    //хилка

    sf::Vector2f v(100,100);
    vector<HealthPoint> health_orbs;
    health_orbs.emplace_back(5, v, font_mk_90, health_orb_texture);

    //враги

    vector<Kamikaze> kamikazes;
    vector<Shooter> shooters;
    vector<ShooterBullet> shooters_bullets;

    constexpr int max_kamikazes = 30;
    constexpr int max_shooters = 6;

    kamikazes.reserve(max_kamikazes);
    shooters.reserve(max_shooters);

    //score

    int score = 0;
    sf::Text score_text;
    score_text.setFont(font_mk_90);
    score_text.setFillColor(sf::Color::White);
    score_text.setString("SCORE: " + to_string(score));
    score_text.setPosition(constants::screen_width/2 - score_text.getGlobalBounds().width/2, 10);

    //меню

    MainMenu main_menu(font_mk_90, play_music, play_sounds);
    PauseMenu pause_menu(font_mk_90, play_sounds, play_music);
    GameOver game_over(font_mk_90,&score);

    //звуки

    sf::SoundBuffer sound_buffer;
    sound_buffer.loadFromFile(rcs + "aud/shoot.wav");
    sf::Sound shoot_sound(sound_buffer);
    sf::Sound shooter_sound(sound_buffer);
    shooter_sound.setPitch(1.3f);

    sf::SoundBuffer click_buffer;
    click_buffer.loadFromFile(rcs + "aud/click2.wav");
    sf::Sound click;
    click.setBuffer(click_buffer);

    //музыка

    sf::Music game_music;
    game_music.openFromFile(rcs + "mus/Sayer_Andromeda.wav");

    //часы для появления врагов

    sf::Clock starting_pause_clock;
    sf::Clock kamikaze_clock;
    sf::Clock shooter_clock;
    sf::Time time_to_shoot = sf::seconds(1);


    //статус игры
    GameStatus game_status = GameStatus::kMainMenu;

    while (window.isOpen())
    {
        sf::Time kamikaze_elapsed_seconds = kamikaze_clock.getElapsedTime();
        sf::Time shooter_elapsed_seconds  = shooter_clock.getElapsedTime();

        sf::Event event{};

        //блок обработки событий
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                switch (game_status)
                {
                    case GameStatus::kPlaying:
                    {
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            if(play_sounds)
                            {
                                shoot_sound.play();
                            }
                            spaceship.Shoot(scope,bullet_texture);
                        }
                    }
                        break;
                    case GameStatus::kMainMenu:
                    {
                        switch (main_menu.HandleClick())
                        {
                            case MainMenuSignal::kSwitchMusic:
                                play_music = !play_music;
                                break;
                            case MainMenuSignal::kSwitchSounds:
                                play_sounds = !play_sounds;
                                break;
                            case MainMenuSignal::kExitGame:
                                window.close();
                                break;
                            case MainMenuSignal::kStartGame:
                                game_status = GameStatus::kPlaying;
                                starting_pause_clock.restart();
                                break;
                            case MainMenuSignal::kNothing:
                                break;
                        }
                    }
                        break;
                    case GameStatus::kPauseMenu:
                    {
                        //if(play_sounds)
                        //{
                        //    click.play();
                        //}
                        switch(pause_menu.HandleClick())
                        {
                            case PauseMenuSignal::kReturn:
                                game_status = GameStatus::kPlaying;
                                break;
                            case PauseMenuSignal::kExit:
                                kamikazes.erase(kamikazes.cbegin(),kamikazes.cend());
                                shooters.erase(shooters.cbegin(),shooters.cend());
                                shooters_bullets.erase(shooters_bullets.cbegin(),shooters_bullets.cend());
                                spaceship.bullets.erase(spaceship.bullets.cbegin(),spaceship.bullets.cend());
                                health_orbs.erase(health_orbs.cbegin(),health_orbs.cend());
                                health_orbs.emplace_back(5, v, font_mk_90, health_orb_texture);
                                spaceship.sprite.setPosition(constants::screen_width/2,constants::screen_height/2);
                                spaceship.AddHealth(1000);
                                score = 0;
                                score_text.setString("SCORE: " + to_string(score));
                                score_text.setPosition(constants::screen_width/2 - score_text.getGlobalBounds().width/2, 10);
                                game_status = GameStatus::kMainMenu;
                                break;
                            case PauseMenuSignal::kSwitchSound:
                                play_sounds = !play_sounds;
                                break;
                            case PauseMenuSignal::kSwitchMusic:
                                play_music = !play_music;
                                break;
                            case PauseMenuSignal::kNothing:
                                break;
                        }
                    }
                        break;
                    case GameStatus::kGameOver:
                    {
                        if(play_sounds)
                        {
                            click.play();
                        }
                        if(game_over.HandleClick(score))
                        {
                            kamikazes.erase(kamikazes.cbegin(),kamikazes.cend());
                            shooters.erase(shooters.cbegin(),shooters.cend());
                            shooters_bullets.erase(shooters_bullets.cbegin(),shooters_bullets.cend());
                            spaceship.bullets.erase(spaceship.bullets.cbegin(),spaceship.bullets.cend());
                            health_orbs.erase(health_orbs.cbegin(),health_orbs.cend());
                            health_orbs.emplace_back(5, v, font_mk_90, health_orb_texture);
                            spaceship.sprite.setPosition(constants::screen_width/2,constants::screen_height/2);
                            spaceship.AddHealth(1000);
                            spaceship.alive = true;
                            game_over.input_box.input.setString("");
                            game_status = GameStatus::kMainMenu;
                            score = 0;
                            score_text.setString("SCORE: " + to_string(score));
                            score_text.setPosition(constants::screen_width/2 - score_text.getGlobalBounds().width/2, 10);

                        }
                    }
                        break;
                }
            }
            if(event.type == sf::Event::MouseMoved)
            {
                switch (game_status)
                {
                    case GameStatus::kPlaying:
                    {
                        scope.setPosition(sf::Mouse::getPosition().x - scope.getGlobalBounds().width / 2,
                                          sf::Mouse::getPosition().y - scope.getGlobalBounds().height / 2);
                        spaceship.UpdateRotation(scope);
                    }
                        break;
                    case GameStatus::kMainMenu:
                    case GameStatus::kPauseMenu:
                    case GameStatus::kGameOver:
                        cursor.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
                        break;
                }
            }
            if(event.type == sf::Event::TextEntered && game_status == GameStatus::kGameOver)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                {
                    game_over.input_box.DeleteChar();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
                         sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
                         event.text.unicode > 127 ||
                         event.text.unicode < 0)
                {/* do nothing */} // для ввода только англ, цифр
                else
                {
                    game_over.input_box.AddChar(event.text.unicode);
                }
            }
        }

        //блок логики
        switch (game_status)
        {
            case GameStatus::kPlaying:
            {
                if(play_music)
                {
                    if (game_music.getStatus() != sf::Music::Playing)
                    {
                        game_music.play();
                    }
                    if (game_music.getPlayingOffset().asSeconds() >= game_music.getDuration().asSeconds() - sf::seconds(1).asSeconds())
                    {
                        game_music.stop();
                    }
                }
                else
                {
                    game_music.stop();
                }

                // управление

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    //window.close();
                    game_status = GameStatus::kPauseMenu;
                }
                spaceship.Move(scope);

                //generate enemies
                //////////////////////////////////////////////////////////////////////////
                sf::Time kamikaze_time_to_spawn = sf::seconds(2);
                sf::Time shooter_time_to_spawn = sf::seconds(3);

                if(starting_pause_clock.getElapsedTime() >= sf::seconds(200))
                {
                    kamikaze_time_to_spawn = sf::seconds(0.5);
                    shooter_time_to_spawn = sf::seconds(1.5);
                }
                else if(starting_pause_clock.getElapsedTime() >= sf::seconds(100))
                {
                    kamikaze_time_to_spawn = sf::seconds(1);
                    shooter_time_to_spawn = sf::seconds(2);
                }

                if(starting_pause_clock.getElapsedTime() > sf::seconds(2))
                {
                    if(kamikaze_elapsed_seconds >= kamikaze_time_to_spawn)
                    {
                        kamikaze_clock.restart();
                        if (kamikazes.size() < max_kamikazes)
                        {
                            kamikazes.emplace_back(kamikaze_texture);
                        }
                    }
                    if(shooter_elapsed_seconds >= shooter_time_to_spawn)
                    {
                        shooter_clock.restart();
                        if (shooters.size() < max_shooters)
                        {
                            shooters.emplace_back(spaceship.sprite.getPosition(), shooter_texture, shooter_light_texture);
                        }
                    }
                }
                /////////////////////////////////////////////////////////////////////////////////
                /////////////////////////////////////////////////////////////////////////////////
                /////////////////////////////////////////////////////////////////////////////////

                for(auto h = health_orbs.begin(); h < health_orbs.end(); ++h)
                {
                    if(Intersect(spaceship.hit_box, h->hit_box))
                    {
                        spaceship.AddHealth(h->hp);
                        health_orbs.erase(h);
                    }
                }

                for(auto it_bullet = spaceship.bullets.begin(); it_bullet < spaceship.bullets.end(); ++it_bullet)
                {
                    if(InsideWindow(it_bullet->sprite))
                    {
                        it_bullet->Move();
                    }
                    else
                    {
                        spaceship.bullets.erase(it_bullet);
                    }
                }
                for(auto it_shooter_bullet = shooters_bullets.begin(); it_shooter_bullet < shooters_bullets.end(); ++it_shooter_bullet)
                {
                    if(InsideWindow(it_shooter_bullet->sprite))
                    {
                        //window.draw(it_shooter_bullet->sprite);
                        it_shooter_bullet->Move();
                    }
                    else
                    {
                        shooters_bullets.erase(it_shooter_bullet);
                    }

                    if(Intersect(it_shooter_bullet->hit_box, spaceship.hit_box))
                    {
                        shooters_bullets.erase(it_shooter_bullet);
                        spaceship.ReduceHealth(Rand(3,5));
                    }
                }
                for(auto it_kamikaze = kamikazes.begin(); it_kamikaze < kamikazes.end(); ++it_kamikaze)
                {
                    it_kamikaze->Move(spaceship.sprite);

                    if(Intersect(it_kamikaze->hit_box, spaceship.hit_box))
                    {
                        kamikazes.erase(it_kamikaze);
                        spaceship.ReduceHealth(Rand(1,2));
                        continue;
                    }

                    for(auto it_bullet = spaceship.bullets.begin(); it_bullet < spaceship.bullets.end(); ++it_bullet)
                    {
                        if (Intersect(it_bullet->hit_box, it_kamikaze->hit_box))
                        {
                            kamikazes.erase(it_kamikaze);
                            spaceship.bullets.erase(it_bullet);
                            score += 5;
                            score_text.setString("SCORE: " + to_string(score));
                            score_text.setPosition(constants::screen_width/2 - score_text.getGlobalBounds().width/2, 10);
                        }
                    }
                }
                for(auto it_shooter = shooters.begin(); it_shooter < shooters.end(); ++it_shooter)
                {
                    it_shooter->Move(spaceship.sprite);
                    it_shooter->shoot_light.setPosition(it_shooter->sprite.getPosition());

                    if(Intersect(it_shooter->hit_box, spaceship.hit_box))
                    {
                        shooters.erase(it_shooter);
                        spaceship.ReduceHealth(Rand(2,3));
                        continue;
                    }

                    if(it_shooter->shoot_clock.getElapsedTime() >= sf::seconds(Rand(200, 100) / 100))
                    {
                        it_shooter->Shoot(spaceship.sprite.getPosition(), shooters_bullets, shooter_bullet_texture);
                        if(InsideWindow(it_shooter->sprite) && play_sounds)
                        {
                            shooter_sound.play();
                        }
                        it_shooter->shoot_clock.restart();
                    }

                    for(auto it_bullet = spaceship.bullets.begin(); it_bullet < spaceship.bullets.end(); ++it_bullet)
                    {
                        if (Intersect(it_bullet->hit_box, it_shooter->hit_box))
                        {
                            if(Rand(0,100)>87)
                            {
                                health_orbs.emplace_back(Rand(2, 4),
                                                         it_shooter->sprite.getPosition(), font_mk_90, health_orb_texture);
                            }
                            shooters.erase(it_shooter);
                            spaceship.bullets.erase(it_bullet);
                            score += 10;
                            score_text.setString("SCORE: " + to_string(score));
                            score_text.setPosition(constants::screen_width/2 - score_text.getGlobalBounds().width/2, 10);
                        }
                    }
                }
                if(!spaceship.alive)
                {
                    game_status = GameStatus::kGameOver;
                }

                /////////////////////////////////////////////////////////////////////////////////
                /////////////////////////////////////////////////////////////////////////////////
                /////////////////////////////////////////////////////////////////////////////////
            }
                break;
            case GameStatus::kMainMenu:
            {
                game_music.stop();
                main_menu.Update();
            }
                break;
            case GameStatus::kPauseMenu:
            {
                if(play_music)
                {
                    if (game_music.getStatus() != sf::Music::Playing)
                    {
                        game_music.play();
                    }
                    if (game_music.getPlayingOffset().asSeconds() >= game_music.getDuration().asSeconds() - sf::seconds(1).asSeconds())
                    {
                        game_music.stop();
                    }
                }
                else
                {
                    game_music.stop();
                }
                pause_menu.Update();
            }
                break;
            case GameStatus::kGameOver:
            {
                if(play_music)
                {
                    if (game_music.getStatus() != sf::Music::Playing)
                    {
                        game_music.play();
                    }
                    if (game_music.getPlayingOffset().asSeconds() >= game_music.getDuration().asSeconds() - sf::seconds(1).asSeconds())
                    {
                        game_music.stop();
                    }
                }
                else
                {
                    game_music.stop();
                }
                game_over.Update();
            }
                break;
        }

        /// DRAW ///

        //блок отрисовки
        window.clear();
        switch (game_status)
        {
            case GameStatus::kPlaying:
            {
                window.draw(back);
                window.draw(background);
                for(auto it_shooter_bullet = shooters_bullets.begin(); it_shooter_bullet < shooters_bullets.end(); ++it_shooter_bullet)
                {
                    window.draw(it_shooter_bullet->sprite);
                    //window.draw(it_shooter_bullet->hit_box); ///test
                }
                for(auto it_kamikaze = kamikazes.begin(); it_kamikaze < kamikazes.end(); ++it_kamikaze)
                {
                    window.draw(it_kamikaze->sprite);
                    //window.draw(it_kamikaze->hit_box); ///test
                }
                for(auto it_shooter = shooters.begin(); it_shooter < shooters.end(); ++it_shooter)
                {
                    if(it_shooter->shoot_light_clock.getElapsedTime() < sf::seconds(0.08f))
                    {
                        window.draw(it_shooter->shoot_light);
                    }
                    window.draw(it_shooter->sprite);
                    //window.draw(it_shooter->hit_box); ///test
                }
                for(const auto& hp : health_orbs)
                {
                    window.draw(hp.sprite);
                    window.draw(hp.text);
                }
                spaceship.Draw(window);
                window.draw(scope);
                window.draw(score_text);
            }
                break;
            case GameStatus::kMainMenu:
            {
                //window.draw(back);
                //window.draw(background);

                window.draw(back);
                main_menu.Draw(window);
                window.draw(cursor);
            }
                break;
            case GameStatus::kPauseMenu:
            {
                window.draw(back);
                window.draw(background);
                for(auto it_shooter_bullet = shooters_bullets.begin(); it_shooter_bullet < shooters_bullets.end(); ++it_shooter_bullet)
                {
                    window.draw(it_shooter_bullet->sprite);
                    //window.draw(it_shooter_bullet->hit_box); ///test
                }
                for(auto it_kamikaze = kamikazes.begin(); it_kamikaze < kamikazes.end(); ++it_kamikaze)
                {
                    window.draw(it_kamikaze->sprite);
                    //window.draw(it_kamikaze->hit_box); ///test
                }
                for(auto it_shooter = shooters.begin(); it_shooter < shooters.end(); ++it_shooter)
                {
                    if(it_shooter->shoot_light_clock.getElapsedTime() < sf::seconds(0.08f))
                    {
                        window.draw(it_shooter->shoot_light);
                    }
                    window.draw(it_shooter->sprite);
                    //window.draw(it_shooter->hit_box); ///test
                }
                for(const auto& hp : health_orbs)
                {
                    window.draw(hp.sprite);
                    window.draw(hp.text);
                }
                spaceship.Draw(window);
                window.draw(score_text);

                pause_menu.Draw(window);
                window.draw(cursor);
            }
                break;
            case GameStatus::kGameOver:
            {
                window.draw(background);
                game_over.Draw(window);
                window.draw(cursor);
            }
                break;
        }
        window.display();
    }

    return 0;
}
