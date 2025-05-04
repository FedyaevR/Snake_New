#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace GameStatePlayingData
{
    struct GameStatePlayingData
    {
        // Resources
        sf::Font font;

        // UI data
        sf::Text scoreText;
        sf::Text inputHintText;

        void InitGameStatePlaying();
        void ShutdownGameStatePlaying();
    };

    void UpdateGameStatePlaying(GameStatePlayingData& data, Core_Game::Game& game);
    void DrawGameStatePlaying(GameStatePlayingData& data, Core_Game::Game& game, sf::RenderWindow& window);
    void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Core_Game::Game& game, const sf::Event& event);
}