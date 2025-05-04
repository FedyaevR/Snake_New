#include <SFML/Graphics.hpp>
#pragma once

namespace GameStateRecordsTable
{
    struct GameStateRecordsTable
    {
        // Resources
        sf::Font font;

        // UI data
        sf::Text scoreText;
        sf::Text inputHintText;

        void InitGameStatePlaying();
        void ShutdownGameStatePlaying();
    };
}