#include "Controller.h"
#include "SFML/Window/Keyboard.hpp"

namespace Core_Controller
{
    void MoveInput(Snake::Snake& snake, Apple::Apple& apple)
    {
        if (snake.IsAlive() == false)
        {
            return;
        }
            
        Snake_Direction::Direction currentDirection = snake.GetDirection();
        Snake_Direction::Direction newDirection = currentDirection;
        

        if (IsMoveUp(currentDirection))
        {
            newDirection = Snake_Direction::Direction::Up;
        }
        else if (IsMoveDown(currentDirection))
        {
            newDirection = Snake_Direction::Direction::Down;
        } 
        else if (IsMoveLeft(currentDirection))
        {
            newDirection = Snake_Direction::Direction::Left;
        } 
        else if (IsMoveRight(currentDirection))
        {
            newDirection = Snake_Direction::Direction::Right;
        }
        
        // Устанавливаем новое направление только если оно изменилось
        if (newDirection != currentDirection)
        {
            snake.SetDirection(newDirection, apple);
        }
    }

    bool IsMoveUp(Snake_Direction::Direction currentDirection)
    {
        if (currentDirection == Snake_Direction::Direction::Down)
        {
            return false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            return true;
        }

        return false;
    }

    bool IsMoveDown(Snake_Direction::Direction currentDirection)
    {
        if (currentDirection == Snake_Direction::Direction::Up)
        {
            return false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            return true;
        }

        return false;
    }

    bool IsMoveLeft(Snake_Direction::Direction currentDirection)
    {
        if (currentDirection == Snake_Direction::Direction::Right)
        {
            return false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            return true;
        }

        return false;
    }

    bool IsMoveRight(Snake_Direction::Direction currentDirection)
    {
        if (currentDirection == Snake_Direction::Direction::Left)
        {
            return false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            return true;
        }

        return false;
    }
}
