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
                    // При движении вверх хвост направлен вниз (вид сверху)
                    texture = bodyAssets.tail.down; 
                    break;
                case Snake_Direction::Direction::Down:
                    // При движении вниз хвост направлен вверх (вид сверху)
                    texture = bodyAssets.tail.up; 
                    break;
                case Snake_Direction::Direction::Left:
                    // При движении влево хвост направлен вправо (вид сверху)
                    texture = bodyAssets.tail.right;
                    break;
                case Snake_Direction::Direction::Right:
                    // При движении вправо хвост направлен влево (вид сверху)
                    texture = bodyAssets.tail.left;
                    break;
                default:
                    texture = bodyAssets.tail.up;
                    break;
            }
        }
        // Для сегментов тела
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
                // Для прямых участков используем стандартные текстуры
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
                    texture = bodyAssets.body.vertical; // По умолчанию
                }
            }
        }

        sprite.setTexture(texture);
    }

    void Segment::UpdateSpritePosition()
    {
        sprite.setPosition(position.x, position.y);
    }
    
    float Segment::CalculateDistance(const Math::Position& pos1, const Math::Position& pos2)
    {
        float dx = pos1.x - pos2.x;
        float dy = pos1.y - pos2.y;

        return std::sqrt(dx * dx + dy * dy);
    }
    
    void Segment::FollowPreviousSegment()
    {
        // Проверяем наличие предыдущего сегмента
        if (previousSegment == nullptr)
        {
            return;
        }

        // Сохраняем текущую позицию и направление
        previousPosition = position;
        
        // Получаем позицию предыдущего сегмента для следования
        Math::Position prevPos = previousSegment->previousPosition;
        
        // Если сегмент следует за головой, используем направление головы
        // для более точного следования
        if (previousSegment->isHead)
        {
            // Рассчитываем вектор движения только для определения направления
            float dx = prevPos.x - position.x;
            float dy = prevPos.y - position.y;
            
            // Определяем основное направление движения
            Snake_Direction::Direction newDirection;
            
            if (std::abs(dx) > std::abs(dy))
            {
                // Горизонтальное движение
                newDirection = (dx > 0) ? Snake_Direction::Direction::Right : Snake_Direction::Direction::Left;
            }
            else
            {
                // Вертикальное движение
                newDirection = (dy > 0) ? Snake_Direction::Direction::Down : Snake_Direction::Direction::Up;
            }
            
            //// Если направление изменилось от предыдущего раза, считаем это поворотом
            //if (newDirection != direction)
            //{
            //    // Сохраняем предыдущее направление и устанавливаем флаг поворота
            //    previousDirection = direction;
            //    isTurn = true;
            //}
            
            // Обновляем направление
            direction = newDirection;
        }
        else
        {
            // Для остальных сегментов рассчитываем вектор движения
            float dx = prevPos.x - position.x;
            float dy = prevPos.y - position.y;
            
            // Определяем основное направление движения
            Snake_Direction::Direction newDirection;
            
            if (std::abs(dx) > std::abs(dy))
            {
                // Горизонтальное движение
                newDirection = (dx > 0) ? Snake_Direction::Direction::Right : Snake_Direction::Direction::Left;
            }
            else
            {
                // Вертикальное движение
                newDirection = (dy > 0) ? Snake_Direction::Direction::Down : Snake_Direction::Direction::Up;
            }
            
            //// Если направление изменилось, устанавливаем флаг поворота
            //if (newDirection != direction)
            //{
            //    // Сначала сохраняем предыдущее направление, затем устанавливаем флаг поворота
            //    previousDirection = direction;
            //    isTurn = true;
            //}
            // Проверяем, не пора ли сбросить флаг поворота
            //else if (isTurn)
            //{
            //    // Если текущий сегмент и предыдущий имеют одинаковое направление,
            //    // и флаг поворота установлен, сбрасываем его
            //    if (previousSegment && previousSegment->direction == direction)
            //    {
            //        isTurn = false;
            //    }
            //}
            
            // Обновляем направление
            direction = newDirection;
        }
        
        // Устанавливаем новую позицию
        position = prevPos;
        
        // Обновляем позицию спрайта
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
