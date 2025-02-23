// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include "Settings.h"
#include "Controller.h"
#include "Snake.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

const std::string RESOURCES_PATH = "Resources/";

int main()
{
    bool isStart = false;
    sf::RenderWindow window(sf::VideoMode(500, 500), "Snake");
    auto settings = Settings::Settings();
    auto snake = Snake::Snake();

    sf::Clock game_clock;
    sf::Time lastTime = game_clock.getElapsedTime();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        sf::Time currentTime = game_clock.getElapsedTime();
        snake.deltaTime = currentTime.asSeconds() - lastTime.asSeconds();
        lastTime = currentTime;

        if (isStart == false)
        {
            snake.Initialize(settings);

            isStart = true;
        }

        Core_Controller::MoveInput(snake);

        window.clear();

        snake.Draw(window);

        window.display();
    }

    return 0;
}
