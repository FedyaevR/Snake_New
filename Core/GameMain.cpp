void Game::Game()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Basic Snake", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    Snake::Snake snake;
    snake.Initialize(Settings::Settings());
    sf::Clock game_clock;
    sf::Time lastTime = game_clock.getElapsedTime();

    while (window.isOpen())
    {
        sf::Event windowEvent;
        while (window.pollEvent(windowEvent))
        {
            if (windowEvent.type == sf::Event::Closed)
                window.close();
        }

        // Получаем deltaTime для обновления змейки
        sf::Time currentTime = game_clock.getElapsedTime();
        snake.deltaTime = currentTime.asSeconds() - lastTime.asSeconds();
        lastTime = currentTime;

        // Обрабатываем пользовательский ввод для установки нового направления
        Controller::MoveInput(snake);
        
        // Обновляем змейку один раз за кадр с текущим направлением
        snake.Update();

        window.clear();
        snake.Draw(window);
        window.display();
    }
} 