#include "Controller.h"
#include "SFML/Window/Keyboard.hpp"

namespace Core_Controller
{
    void MoveInput(Snake::Snake& snake)
    {
        // Проверяем, жива ли змейка
        if (!snake.IsAlive())
            return;
            
        // Получаем текущее направление
        Snake_Direction::Direction currentDirection = snake.GetDirection();
        
        // Определяем новое направление на основе ввода пользователя
        Snake_Direction::Direction newDirection = currentDirection;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && currentDirection != Snake_Direction::Direction::Down)
        {
            newDirection = Snake_Direction::Direction::Up;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && currentDirection != Snake_Direction::Direction::Up)
        {
            newDirection = Snake_Direction::Direction::Down;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && currentDirection != Snake_Direction::Direction::Right)
        {
            newDirection = Snake_Direction::Direction::Left;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && currentDirection != Snake_Direction::Direction::Left)
        {
            newDirection = Snake_Direction::Direction::Right;
        }
        
        // Устанавливаем новое направление только если оно изменилось
        if (newDirection != currentDirection)
        {
            snake.SetDirection(newDirection);
        }
    }
}
