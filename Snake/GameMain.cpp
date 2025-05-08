// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include "Settings.h"
#include "Game.h"
#include "Snake.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

const std::string RESOURCES_PATH = "Resources/";

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Snake");

    Core_Game::Game game;
    game.settings.screenWidth = window.getSize().x;
    game.settings.screenHeight = window.getSize().y;

    sf::Clock game_clock;
    sf::Time lastTime = game_clock.getElapsedTime();

    window.setKeyRepeatEnabled(true);

    // Game loop
    while (window.isOpen())
    {
        sf::Time currentTime = game_clock.getElapsedTime();
        game.deltaTime = currentTime.asSeconds() - lastTime.asSeconds();
        lastTime = currentTime;

        game.HandleWindowEvents(window);

        if (!window.isOpen())
        {
            break;
        }

        if (game.UpdateGame())
        {
            window.clear();
            game.DrawGame(window);
            window.display();

            if (game.wasPause)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(Settings::TIME_FOR_DELAY_AFTER_PAUSE));
                game.wasPause = false;
            }
        }
        else
        {
            window.close();
        }
    }

    return 0;
}
