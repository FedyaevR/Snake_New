#pragma once
#include "Menu.h"
#include "Game.h"

namespace GameStateMainMenuData
{
    struct GameStateMainMenuData
    {
        sf::Font font;

        Menu::MenuItem startGameItem;
        Menu::MenuItem settings;

        Menu::MenuItem settings;
        Menu::MenuItem settingsMusic;
        Menu::MenuItem settingsSound;

        Menu::MenuItem difficultyLevel;
        Menu::MenuItem difficultyEasyLevel;
        Menu::MenuItem difficultyHarderThanEasyLevel;
        Menu::MenuItem difficultyMediumLevel;
        Menu::MenuItem difficultyEasierThanHardLevel;
        Menu::MenuItem difficultyHardLevel;
        Menu::MenuItem exitGameItem;
        Menu::MenuItem yesItem;
        Menu::MenuItem noItem;
        Menu::Menu menu;

        void InitGameStateMainMenu();
        void ShutdownGameStateMainMenu();
    };

    void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Core_Game::Game& game, const sf::Event& event);
    void UpdateGameStateMainMenu(GameStateMainMenuData& data, float timeDelta);
    void DrawGameStateMainMenu(GameStateMainMenuData& data, sf::RenderWindow& window);
}