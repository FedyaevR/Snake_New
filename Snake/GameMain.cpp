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
    settings.deltaTime = 0.0f;
    
    settings.partSize = Settings::SNAKE_PART_SIZE;
    settings.screenWidth = 500;
    settings.screenHeight = 500;
    settings.moveSpeed = 0.25f;
    
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
        float deltaTime = currentTime.asSeconds() - lastTime.asSeconds();
        lastTime = currentTime;

        if (isStart == false)
        {
            snake.Initialize(settings);
            isStart = true;
        }

        // Обрабатываем ввод (только устанавливает направление)
        Core_Controller::MoveInput(snake);
        
        // Обновляем змейку один раз за кадр, передаем deltaTime
        snake.Update(deltaTime);

        window.clear();
        snake.Draw(window);
        window.display();
    }

    return 0;
}
