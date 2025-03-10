#include "Controller.h"

namespace Core_Controller
{
    void MoveInput(Snake::Snake& snake)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == false)
        {
            snake.head->direction = Snake_Direction::Direction::Up;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == false)
        {
            snake.head->direction = Snake_Direction::Direction::Down;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == false)
        {
            snake.head->direction = Snake_Direction::Direction::Left;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == false)
        {
            snake.head->direction = Snake_Direction::Direction::Right;
        }

        snake.Update(snake.head->direction);
    }
}
