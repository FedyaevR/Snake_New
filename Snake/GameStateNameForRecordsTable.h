#include "Game.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>
#pragma once

namespace GameStateNameForRecordsTable
{
    struct GameStateNameForRecordsTable
    {
        // Resources
        sf::Font font;

        Menu::Menu menu;
        Menu::MenuItem yesItem;
        Menu::MenuItem noItem;
        Menu::MenuItem inputItem;

        sf::Text inputNameText;
        std::string userName;
        

        void InitGameStateNameForRecords();
    };

    void HandleGameStateNameForRecordWindowEvent(GameStateNameForRecordsTable& data, Core_Game::Game& game, const sf::Event& event);
    void UpdateGameStateNameForRecord(GameStateNameForRecordsTable& data, float timeDelta, Core_Game::Game& game);
    void DrawGameStateNameForRecord(GameStateNameForRecordsTable& data, sf::RenderWindow& window);
}