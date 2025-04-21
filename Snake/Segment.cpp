#include "Segment.h"
#include <cmath>
#include <iostream>

namespace Snake_Segment
{
    void Segment::SetPosition(Math::Position setPosition)
    {
        previousPosition = position;
        position.x = setPosition.x;
        position.y = setPosition.y;

        UpdateSpritePosition();
    }

    void Segment::SetTurnFlag(Snake_Direction::Direction newDirection)
    {
        
        if (direction != newDirection)
        {
            isTurn = true;
            previousDirection = direction;
        }
        else
        {
            isTurn = false;
        }
    }

    void Segment::SetTexture(Snake_Direction::Direction setDirection, Views::SnakeBodyViews bodyAssets)
    {
        // Для головы
        if (isHead)
        {
            switch (setDirection)
            {
                case Snake_Direction::Direction::Up:
                    texture = bodyAssets.head.up;
                    break;
                case Snake_Direction::Direction::Down:
                    texture = bodyAssets.head.down;
                    break;
                case Snake_Direction::Direction::Left:
                    texture = bodyAssets.head.left;
                    break;
                case Snake_Direction::Direction::Right:
                    texture = bodyAssets.head.right;
                    break;
                default:
                    texture = bodyAssets.head.up;
                    break;
            }
        }
        // Для хвоста
        else if (isTail)
        {
            switch (setDirection)
            {
                case Snake_Direction::Direction::Up:
                    // При движении вверх хвост направлен вниз
                    texture = bodyAssets.tail.down; 
                    break;
                case Snake_Direction::Direction::Down:
                    // При движении вниз хвост направлен вверх
                    texture = bodyAssets.tail.up; 
                    break;
                case Snake_Direction::Direction::Left:
                    // При движении влево хвост направлен вправо
                    texture = bodyAssets.tail.right;
                    break;
                case Snake_Direction::Direction::Right:
                    // При движении вправо хвост направлен влево
                    texture = bodyAssets.tail.left;
                    break;
                default:
                    texture = bodyAssets.tail.up;
                    break;
            }
        }
        else
        {
            if (isTurn)
            {
                // Используем метод GetBodyTexture из SnakeBodyAssets для определения нужной текстуры поворота
                // Этот метод содержит корректную логику определения всех типов угловых соединений
                texture = bodyAssets.GetBodyTexture(previousDirection, setDirection);
            }
            else
            {
                if (setDirection == Snake_Direction::Direction::Up || setDirection == Snake_Direction::Direction::Down)
                {
                    texture = bodyAssets.body.vertical;
                }
                else if (setDirection == Snake_Direction::Direction::Left || setDirection == Snake_Direction::Direction::Right)
                {
                    texture = bodyAssets.body.horizontal;
                }
                else
                {
                    texture = bodyAssets.body.vertical; 
                }
            }
        }

        sprite.setTexture(texture);
    }

    void Segment::UpdateSpritePosition()
    {
        sprite.setPosition(position.x, position.y);
    }
    
    float Segment::CalculateDistance(const Math::Position& position1, const Math::Position& position2)
    {
        float dx = position1.x - position2.x;
        float dy = position1.y - position2.y;

        return std::sqrt(dx * dx + dy * dy);
    }
    
    void Segment::FollowPreviousSegment()
    {
        if (previousSegment == nullptr)
        {
            return;
        }

        previousPosition = position;
        Math::Position prevSegmentPosition = previousSegment->previousPosition;
        
        float dx = prevSegmentPosition.x - position.x;
        float dy = prevSegmentPosition.y - position.y;
            
        Snake_Direction::Direction newDirection;
            
        if (std::abs(dx) > std::abs(dy))
        {
            newDirection = (dx > 0) ? Snake_Direction::Direction::Right : Snake_Direction::Direction::Left;
        }
        else
        {
            newDirection = (dy > 0) ? Snake_Direction::Direction::Down : Snake_Direction::Direction::Up;
        }

        direction = newDirection;
        position = prevSegmentPosition;
        
        UpdateSpritePosition();
    }

    bool Segment::CheckCollision(const Segment& other)
    {
        // Расчет расстояния между центрами сегментов
        float distance = CalculateDistance(position, other.position);
        
        // Считаем столкновением, если расстояние меньше размера сегмента
        // Используем коэффициент 0.8 для создания небольшого зазора
        return distance < targetDistance * 0.8f;
    }
}
