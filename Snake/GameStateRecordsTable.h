#include <SFML/Graphics.hpp>
#include "Menu.h"
#pragma once

namespace GameStateNameForRecordsTable
{
    struct GameStateNameForRecordsTable
    {
        // Resources
        sf::Font font;

        Menu::MenuItem inputNameMenuItem;
        Menu::MenuItem yesItem;
        Menu::MenuItem noItem;
        

        void InitGameStatePlaying();
    };
}