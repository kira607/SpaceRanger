//
// Created by Lad on 07.05.2020.
//

#include "spaceship.h"

Spaceship::Spaceship(const sf::Texture& texture, const sf::Texture& light_texture)
{
    alive = true;
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setScale(0.2f, 0.2f);
    sprite.setPosition(constants::screen_width / 2, constants::screen_height / 2);

    hit_box.setRadius(sprite.getGlobalBounds().height * 0.3f);
    hit_box.setPointCount(30);
    hit_box.setFillColor(sf::Color(255,127,127,127));
    UpdateHitBoxPosition();

    health_point.setSize(sf::Vector2f(20,20));
    health_point.setPosition(10,1050);

    health_bar_frame.setSize(sf::Vector2f(health_bar_max_size,20));
    health_bar_frame.setFillColor(sf::Color(0,0,0,0));
    health_bar_frame.setOutlineColor(sf::Color(100,100,100,255));
    health_bar_frame.setOutlineThickness(3);
    health_bar_frame.setPosition(5,constants::screen_height-20-5);

    health_bar.setSize(health_bar_frame.getSize());
    health_bar.setFillColor(colors::start_health_bar_color);
    health_bar.setPosition(health_bar_frame.getPosition());

    shoot_light.setTexture(light_texture);
    shoot_light.setOrigin(shoot_light.getGlobalBounds().width/2, shoot_light.getGlobalBounds().height/2);
    shoot_light.setScale(1.1f,1.1f);
}
void Spaceship::UpdateRotation(const sf::Sprite& scope)
{
    float dX = scope.getPosition().x - sprite.getPosition().x;
    float dY = scope.getPosition().y - sprite.getPosition().y;
    float angle = atan2(dY, dX) * 180 / constants::pi;
    sprite.setRotation(angle);
}
void Spaceship::UpdateHitBoxPosition()
{
    hit_box.setPosition(sprite.getPosition().x-hit_box.getRadius(),sprite.getPosition().y-hit_box.getRadius());
}

void Spaceship::Move(const sf::Sprite& scope)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if(sprite.getPosition().y - sprite.getGlobalBounds().height/2 >= 0)
        {
            MoveUp();
        }
        UpdateRotation(scope);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if(sprite.getPosition().x - sprite.getGlobalBounds().width/2 >= 0)
        {
            MoveLeft();
        }
        UpdateRotation(scope);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if(sprite.getPosition().y + sprite.getGlobalBounds().height/2 <= constants::screen_height)
        {
            MoveDown();
        }
        UpdateRotation(scope);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if(sprite.getPosition().x + sprite.getGlobalBounds().width/2 <= constants::screen_width)
        {
            MoveRight();
        }
        UpdateRotation(scope);
    }
}
void Spaceship::MoveUp()
{
    sprite.move(0, -speed);
    UpdateHitBoxPosition();
}
void Spaceship::MoveLeft()
{
    sprite.move(-speed, 0);
    UpdateHitBoxPosition();
}
void Spaceship::MoveDown()
{
    sprite.move(0, speed);
    UpdateHitBoxPosition();
}
void Spaceship::MoveRight()
{
    sprite.move(speed, 0);
    UpdateHitBoxPosition();
}

void Spaceship::ReduceHealth(int health_to_reduce)
{
    if(health_points > health_to_reduce)
    {
        health_points -= health_to_reduce;
        sf::Vector2f new_size;
        new_size.x = health_bar.getSize().x - (health_bar_max_size/100) * health_to_reduce;
        new_size.y = health_bar.getSize().y;
        health_bar.setSize(new_size);
        UpdateHealthBarColor();
    }
    else
    {
        alive = false;
    }
}
void Spaceship::AddHealth(int health_to_add)
{
    if(health_points + health_to_add <= 100)
    {
        health_points += health_to_add;
        sf::Vector2f new_size;
        new_size.x = health_bar.getSize().x + (health_bar_max_size/100) * health_to_add;
        new_size.y = health_bar.getSize().y;
        health_bar.setSize(new_size);
    }
    else
    {
        health_points = 100;
        sf::Vector2f new_size;
        new_size.x = health_bar_max_size;
        new_size.y = health_bar.getSize().y;
        health_bar.setSize(new_size);
    }
    UpdateHealthBarColor();
}
void Spaceship::UpdateHealthBarColor()
{
    int green = health_points * 2;
    int red = 200 - green;
    health_bar.setFillColor(sf::Color(red,green,10,250));
}

void Spaceship::Shoot(const sf::Sprite& scope, const sf::Texture& texture)
{
    bullets.emplace_back(this,scope,texture);
    shoot_light_clock.restart();
}

void Spaceship::Draw(sf::RenderWindow& window)
{
    //window.draw(hit_box); /// test
    if(shoot_light_clock.getElapsedTime() < sf::seconds(0.08f))
    {
        shoot_light.setPosition(sprite.getPosition());
        window.draw(shoot_light);
    }

    for(auto it_bullet = bullets.begin(); it_bullet < bullets.end(); ++it_bullet)
    {
        window.draw(it_bullet->sprite);
        //window.draw(it_bullet->hit_box); ///test
    }

    window.draw(sprite);
    window.draw(health_bar_frame);
    window.draw(health_bar);
}