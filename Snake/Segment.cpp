#include "Segment.h"

namespace Snake_Segment
{
    void Snake_Segment::Segment::SetPosition(Math::Position setPosition)
    {
        position.x = setPosition.x;
        position.y = setPosition.y;

        UpdateSpritePosition();
    }

    void Segment::SetTurnFlag(Snake_Direction::Direction setDirection)
    {
        if (direction != setDirection)
        {
            isTurn = true;
        }
        else if (direction == setDirection)
        {
            isTurn = false;
        }
    }


    // Тут надо добавить обновление текстуры тела, сейчас только голова и хвост
    void Segment::SetTexture(Snake_Direction::Direction setDirection, Views::SnakeBodyViews bodyAssets)
    {
        switch (setDirection)
        {
            case Snake_Direction::Direction::Up:
                if (isHead)
                {
                    texture = bodyAssets.head.up;

                    break;
                }
                else if (isTail)
                {
                    texture = bodyAssets.tail.up;

                    break;
                }

                texture = bodyAssets.GetBodyTexture(direction, setDirection);

                break;
            case Snake_Direction::Direction::Down:
                if (isHead)
                {
                    texture = bodyAssets.head.down;

                    break;
                }
                else if (isTail)
                {
                    texture = bodyAssets.tail.down;

                    break;
                }

                texture = bodyAssets.GetBodyTexture(direction, setDirection);

                break;
            case Snake_Direction::Direction::Left:
                if (isHead)
                {
                    texture = bodyAssets.head.left;

                    break;
                }
                else if (isTail)
                {
                    texture = bodyAssets.tail.left;

                    break;
                }

                texture = bodyAssets.GetBodyTexture(direction, setDirection);

                break;
            case Snake_Direction::Direction::Right:
                if (isHead)
                {
                    texture = bodyAssets.head.right;

                    break;
                }
                else if (isTail)
                {
                    texture = bodyAssets.tail.right;

                    break;
                }

                texture = bodyAssets.GetBodyTexture(direction, setDirection);

                break;
        }

        sprite.setTexture(texture);
    }

    void Segment::UpdateSpritePosition()
    {
        sprite.setPosition(position.x, position.y);
    }
}
