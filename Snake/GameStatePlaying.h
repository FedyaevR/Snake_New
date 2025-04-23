#pragma once
#include <SFML/Graphics.hpp>
#include "Controller.h"
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

    void UpdateGameStatePlaying(GameStatePlayingData& data, float timeDelta);
    void DrawGameStatePlaying(GameStatePlayingData& data, sf::RenderWindow& window);
    void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Core_Controller::Controller& controller, const sf::Event& event);
}