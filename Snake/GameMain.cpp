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
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    bool isStart = false;
    sf::RenderWindow window(sf::VideoMode(500, 500), "Snake");
    auto settings = Settings::Settings();
    settings.deltaTime = 0.0f;

    settings.partSize = Settings::SNAKE_PART_SIZE;
    settings.screenWidth = 500;
    settings.screenHeight = 500;
    settings.moveSpeed = 0.25f;

    auto snake = Snake::Snake();
    auto controller = Core_Controller::Controller();
    auto apple = Apple::Apple();

    sf::Clock game_clock;
    sf::Time lastTime = game_clock.getElapsedTime();

    //while (window.isOpen())
    //{
    //    sf::Event event;
    //    while (window.pollEvent(event))
    //    {
    //        if (event.type == sf::Event::Closed)
    //        {
    //            window.close();
    //        }
    //    }

    //    sf::Time currentTime = game_clock.getElapsedTime();
    //    float deltaTime = currentTime.asSeconds() - lastTime.asSeconds();
    //    lastTime = currentTime;

    //    if (isStart == false)
    //    {
    //        snake.Initialize(settings);
    //        apple.GenerateApplePosition(settings, snake);
    //        isStart = true;
    //    }

    //    controller.MoveInput(snake, apple);

    //    snake.Update(deltaTime, apple);

    //    window.clear();
    //    snake.Draw(window);
    //    apple.Draw(window);
    //    window.display();
    //}

    controller.gameStateChangeType = GameState::GameStateChangeType::None;
    controller.pendingGameStateType = GameState::GameStateType::None;
    controller.pendingGameStateIsExclusivelyVisible = false;
    controller.SwitchGameState(GameState::GameStateType::MainMenu);

    // Game loop
    while (window.isOpen())
    {
        controller.HandleWindowEvents(window);

        if (!window.isOpen())
        {
            break;
        }

        // Calculate time delta
        sf::Time currentTime = game_clock.getElapsedTime();
        float timeDelta = currentTime.asSeconds() - lastTime.asSeconds();
        lastTime = currentTime;
        if (controller.UpdateGame(timeDelta))
        {
            // Draw everything here
            // Clear the window first
            window.clear();

            controller.DrawGame(window);

            // End the current frame, display window contents on screen
            window.display();
        }
        else
        {
            window.close();
        }
    }


    return 0;
}
