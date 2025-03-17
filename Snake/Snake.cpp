#include "Snake.h"
#include "Math.h"
#include <iostream>

namespace Snake
{
    void Snake::Initialize(Settings::Settings settings)
    {
        deltaTime = settings.deltaTime;

        auto head = InitSegment(bodyAssets.head.up, { 500 / 2, 500 / 2 }); // Заменить потом на настройки высоты и ширина экрана
        head.isHead = true;
        auto body1 = InitSegment(bodyAssets.body.vertical, {head.position.x, head.position.y + Settings::SNAKE_PART_SIZE });
        auto body2 = InitSegment(bodyAssets.body.vertical, { body1.position.x, body1.position.y + Settings::SNAKE_PART_SIZE });


        segments.push_back(head);
        segments.push_back(body1);
        segments.push_back(body2);

        this->head = &segments[0];

        Update(head.direction);
    }

    Snake_Segment::Segment Snake::InitSegment(sf::Texture texture, Math::Position position)
    {
        auto segment = Snake_Segment::Segment();

        segment.texture = texture;

        segment.SetPosition(position);
        segment.direction = Snake_Direction::Direction::Up;

        segment.sprite.setTexture(segment.texture);
        segment.sprite.setOrigin(Math::GetItemOrigin(segment.sprite, { 0.5f, 0.5f }));
        segment.sprite.setScale(Math::GetSpriteScale(segment.sprite, { Settings::SNAKE_PART_SIZE, Settings::SNAKE_PART_SIZE }));

        return segment;
    }


    void Snake::Update(Snake_Direction::Direction setDirection)
    {
        MoveHead(setDirection);
        MoveBody();
        UpdateSegmentsTexture(bodyAssets);
    }

    void Snake::MoveHead(Snake_Direction::Direction setDirection)
    {
        //// Запоминаем точку поворота, если направление изменилось
        if (head->direction != setDirection)
        {
            turnPositions.push_back({ head->position, setDirection });
            head->direction = setDirection;
            std::cout << "Turn point added: (" << head->position.x << ", " << head->position.y << ")\n";
        }

        SegmentStep(*head, setDirection);
    }

    void Snake::MoveBody()
    {
        //for (int i = 1; i < segments.size(); i++)
        //{
        //    segments[i].SetTurnFlag(segments[i - 1].direction);
        //    SegmentStep(segments[i], segments[i].direction);
        //}

        for (int i = 1; i < segments.size(); i++)
        {
            // Проверяем, достиг ли сегмент точки поворота
            if (!turnPositions.empty() && IsAtTurnPoint(segments[i].position, turnPositions.front().position))
            {
                segments[i].direction = turnPositions.front().direction;
                segments[i].position = turnPositions.front().position;
                if (i == segments.size() - 1) // Если это последний сегмент, удаляем точку поворота
                {
                    turnPositions.pop_front();
                }
            }

            SegmentStep(segments[i], segments[i].direction);
        }
    }

    void Snake::SegmentStep(Snake_Segment::Segment& segment, Snake_Direction::Direction setDirection)
    {
        float distance = std::min(speed * deltaTime, Settings::SNAKE_PART_SIZE / 2.f);

        //segment.SetTurnFlag(setDirection);

      /*  if (segment.isTurn)
        {
            turnPositions.push_back({ segment.position, setDirection});
            setDirection = head->direction;
        }*/

        switch (setDirection)
        {
            case Snake_Direction::Direction::Up:
                segment.position.y -= distance;

                break;
            case Snake_Direction::Direction::Down:
                segment.position.y += distance;

                break;
            case Snake_Direction::Direction::Left:
                segment.position.x -= distance;

                break;
            case Snake_Direction::Direction::Right:
                segment.position.x += distance;

                break;
        }


        //UpdateSegmentsTexture(setDirection, bodyAssets);
        //UpdateSegmentsTexture(bodyAssets);

        //std::cout << "Segment moved to: (" << segment.position.x << ", " << segment.position.y << ")\n";
        segment.UpdateSpritePosition();

        //if (segment.isTurn)
        //{
        //    turnPositions.push_back(segment.position);
        //    setDirection = head->direction;
        //}

        segment.direction = setDirection;
    }

    bool Snake::IsAtTurnPoint(Math::Position segmentPosition, Math::Position turnPosition)
    {
        const float epsilon = 1.f; // Допуск для точности
        // Отладочный вывод
        std::cout << "Segment position: (" << segmentPosition.x << ", " << segmentPosition.y << ")\n";
        std::cout << "Turn position: (" << turnPosition.x << ", " << turnPosition.y << ")\n";
        return std::abs(segmentPosition.x - turnPosition.x) <= epsilon &&
               std::abs(segmentPosition.y - turnPosition.y) <= epsilon;
    }

    //void Snake::UpdateSegmentsTexture(Snake_Direction::Direction setDirection, Views::SnakeBodyViews bodyAssets)
    //{
    //    for (auto& segment : segments)
    //    {
    //        segment.SetTexture(setDirection, bodyAssets);
    //    }
    //}

    void Snake::UpdateSegmentsTexture(Views::SnakeBodyViews bodyAssets)
    {
        for (size_t i = 0; i < segments.size(); i++)
        {
            Snake_Direction::Direction prevDirection = (i == 0) ? head->direction : segments[i - 1].direction;
            segments[i].SetTexture(segments[i].direction, bodyAssets);
        }
    }

    void Snake::Draw(sf::RenderWindow& window)
    {
        for(auto& segment : segments)
        {
            window.draw(segment.sprite);
        }
    }
}
