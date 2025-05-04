#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

namespace GameStateGameOverData
{
    struct GameStateGameOverData
    {
        // Resources
        sf::Font font;

        float timeSinceGameOver = 0.f;

        // UI data
        sf::Text gameOverText;
        sf::Text hintText;
        sf::Text recordsTableText;

        void InitGameStateGameOver();
        void ShutdownGameStateGameOver();
    };

    void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Core_Game::Game& game, const sf::Event& event);
    void UpdateGameStateGameOver(GameStateGameOverData& data, float timeDelta);
    void DrawGameStateGameOver(GameStateGameOverData& data, sf::RenderWindow& window);
}