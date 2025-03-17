#include "Controller.h"

namespace Core_Controller
{
    void MoveInput(Snake::Snake& snake)
    {
        //auto setDirection = Snake_Direction::Direction::Up;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == false and snake.head->direction != Snake_Direction::Direction::Down)
        {
            //setDirection = Snake_Direction::Direction::Up;
            snake.Update(Snake_Direction::Direction::Up);

            return;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == false and snake.head->direction != Snake_Direction::Direction::Up)
        {
            //setDirection = Snake_Direction::Direction::Down;
            snake.Update(Snake_Direction::Direction::Down);

            return;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == false and snake.head->direction != Snake_Direction::Direction::Right)
        {
            //setDirection = Snake_Direction::Direction::Left;
            snake.Update(Snake_Direction::Direction::Left);

            return;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == false and snake.head->direction != Snake_Direction::Direction::Left)
        {
            //setDirection = Snake_Direction::Direction::Right;
            snake.Update(Snake_Direction::Direction::Right);

            return;
        }

        snake.Update(snake.head->direction);
    }
}
