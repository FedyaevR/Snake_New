#include "SnakeBodyAssets.h"
#include "Direction.h"

namespace Views
{
    sf::Texture SnakeBodyViews::GetBodyTexture(Snake_Direction::Direction previousDirection, Snake_Direction::Direction setDirection)
    {
        if (previousDirection == Snake_Direction::Direction::Up and setDirection == Snake_Direction::Direction::Left)
        {
            return body.bottomLeft;
        }
        else if (previousDirection == Snake_Direction::Direction::Up and setDirection == Snake_Direction::Direction::Right)
        {
            return body.bottomRight;
        }
        else if (previousDirection == Snake_Direction::Direction::Left and setDirection == Snake_Direction::Direction::Up)
        {
            return body.topRight;
        }
        else if (previousDirection == Snake_Direction::Direction::Right and setDirection == Snake_Direction::Direction::Up)
        {
            return body.topLeft;
        }
        else if (previousDirection == Snake_Direction::Direction::Left and setDirection == Snake_Direction::Direction::Down)
        {
            return body.bottomRight;
        }
        else if (previousDirection == Snake_Direction::Direction::Right and setDirection == Snake_Direction::Direction::Down)
        {
            return body.bottomLeft;
        }
        else if (previousDirection == Snake_Direction::Direction::Down and setDirection == Snake_Direction::Direction::Left)
        {
            return body.topLeft;
        }
        else if (previousDirection == Snake_Direction::Direction::Down and setDirection == Snake_Direction::Direction::Right)
        {
            return body.topRight;
        }
        else if (previousDirection == setDirection)
        {
            GetStandartBodyTexture(setDirection);
        }
    }

    sf::Texture SnakeBodyViews::GetStandartBodyTexture(Snake_Direction::Direction direction)
    {
        if (direction == Snake_Direction::Direction::Up or direction == Snake_Direction::Direction::Down)
        {
            return body.vertical;
        }
        else if (direction == Snake_Direction::Direction::Left or direction == Snake_Direction::Direction::Right)
        {
            return body.horizontal;
        }
    }
}
