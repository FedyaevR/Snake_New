#pragma once
#include <SFML/Graphics.hpp>

namespace Math
{
    struct Position
    {
        float x;
        float y;
    };


    sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Position& relativePosition);

    //А точно Positin тут нужен?)
    sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Position& desiredSize);
}