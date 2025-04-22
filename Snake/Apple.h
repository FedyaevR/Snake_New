#include "Math.h"
#include "AppleAsset.h"
#include <SFML/Graphics.hpp>

#pragma once

namespace Snake { struct Snake; }

namespace Apple
{
    struct Apple
    {
        Views::AppleAsset asset;
        Math::Position position;

        Apple()
        {
            asset = Views::AppleAsset();
        }

        void GenerateApplePosition(Settings::Settings settings, Snake::Snake snake);
        void UpdateSpritePosition();
        void Draw(sf::RenderWindow& window);
    };
}