#include "Controller.h"

namespace Core_Controller
{
    // Добавить проверку направлений. Например если направление вверх, то вниз нельзя. Сейчас проверяю только клавиши. СКорей всего это лишнее
    void MoveInput(Snake::Snake& snake)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == false)
        {
            //snake.Update(Snake_Direction::Direction::Up);
            snake.head->direction = Snake_Direction::Direction::Up;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == false)
        {
            //snake.Update(Snake_Direction::Direction::Down);
            snake.head->direction = Snake_Direction::Direction::Down;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == false)
        {
            //snake.Update(Snake_Direction::Direction::Left);
            snake.head->direction = Snake_Direction::Direction::Left;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == false)
        {
            //snake.Update(Snake_Direction::Direction::Right);
            snake.head->direction = Snake_Direction::Direction::Right;
        }

        snake.Update(snake.head->direction);
    }
}
