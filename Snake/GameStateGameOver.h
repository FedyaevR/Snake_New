#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"

namespace GameStateGameOverData
{
    struct GameStateGameOverData
    {
        // Resources
        sf::Font font;

        float timeSinceGameOver = 0.f;

        // UI data
        sf::Text recordsTableText;
        sf::Text scoreText;

        Menu::Menu menu;
        Menu::MenuItem restartGameItem;
        Menu::MenuItem inMainMenu;

        void InitGameStateGameOver();
        void ShutdownGameStateGameOver();
    };

    void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Core_Game::Game& game, const sf::Event& event);
    void UpdateGameStateGameOver(GameStateGameOverData& data, Core_Game::Game& game, float timeDelta);
    void DrawGameStateGameOver(GameStateGameOverData& data, sf::RenderWindow& window);
}