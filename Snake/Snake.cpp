#include "Snake.h"
#include "Math.h"
#include <iostream>
#include <cmath>

struct TurnPoint
{
    Math::Position position;
    Snake_Direction::Direction direction;
};

namespace Snake
{
    void Snake::Initialize(Settings::Settings settings)
    {
        this->settings = settings;
        deltaTime = settings.deltaTime;
        turnPositions.clear();
        segments.clear();

        // Инициализация головы
        InitSegment(true);

        // Инициализация тела
        for (size_t i = 0; i < Settings::SNAKE_INIT_BODY_PART_COUNT; i++)
        {
            InitSegment();
        }

        // Инициализация хвоста
        InitSegment(false, true);

        // Сохраняем указатель на голову для быстрого доступа
        this->head = segments[0];

        // Связываем сегменты между собой
        for (size_t i = 1; i < segments.size(); i++)
        {
            segments[i]->previousSegment = segments[i - 1];
        }

        // Обновляем текстуры сегментов
        for (auto& segment : segments)
        {
            segment->SetTexture(segment->direction, bodyAssets);
        }

        // Сбрасываем счет и статус
        score = 0;
        alive = true;
        accumulator = 0.0f;

    }

    void Snake::InitSegment(bool isHead, bool isTail, Snake_Direction::Direction setDirection)
    {
        const float centerX = settings.screenWidth / 2.0f;
        const float centerY = settings.screenHeight / 2.0f;

        // Расстояние между сегментами
        float segmentGap = (settings.partSize * 0.95f) * segments.size();

        if (isHead)
        {
            segmentGap = 0.f;
        }

        auto segment = InitSegment(bodyAssets.body.vertical, { centerX, centerY + segmentGap });
        segment->isHead = isHead;
        segment->isTail = isTail;
        segment->previousPosition = segment->position;
        segment->direction = setDirection;
        segment->previousDirection = setDirection;

        segments.push_back(segment);
    }

    std::shared_ptr<Snake_Segment::Segment> Snake::InitSegment(sf::Texture texture, Math::Position position)
    {
        auto segment = std::make_shared<Snake_Segment::Segment>(Snake_Segment::Segment());

        segment->texture = texture;
        segment->position = position;

        segment->sprite.setTexture(segment->texture);
        segment->sprite.setOrigin(Math::GetItemOrigin(segment->sprite, { 0.5f, 0.5f }));
        segment->sprite.setScale(Math::GetSpriteScale(segment->sprite, { settings.partSize, settings.partSize }));
        segment->UpdateSpritePosition();

        return segment;
    }

    void Snake::Update(float deltaTime, Apple::Apple& apple)
    {
        if (alive == false)
        {
            return;
        }

        // Закладка на возможное будущее, не уверен, что пока будет использоваться
        accumulator += deltaTime;

        float moveInterval = settings.moveSpeed / speed;

        if (accumulator < moveInterval)
        {
            return;
        }

        accumulator = 0.0f;

        MoveSnake(apple);
    }

    void Snake::MoveSnake(Apple::Apple& apple)
    {
        head->previousPosition = head->position;

        MoveHead();
        if (CheckCollisions(apple, true))
        {
            apple.GenerateApplePosition(settings, *this);
            AddSegment();
        }
        MoveBody();
        CheckCollisions();

        for (auto& segment : segments)
        {
            segment->SetTexture(segment->direction, bodyAssets);
        }
    }

    void Snake::MoveHead()
    {
        Math::Position newPosition = head->position;

        switch (head->direction)
        {
        case Snake_Direction::Direction::Up:
            newPosition.y -= settings.partSize;
            break;
        case Snake_Direction::Direction::Down:
            newPosition.y += settings.partSize;
            break;
        case Snake_Direction::Direction::Left:
            newPosition.x -= settings.partSize;
            break;
        case Snake_Direction::Direction::Right:
            newPosition.x += settings.partSize;
            break;
        default:
            break;
        }

        if (newPosition.x < 0)
        {
            newPosition.x = settings.screenWidth - settings.partSize;
        }
        else if (newPosition.x >= settings.screenWidth)
        {
            newPosition.x = 0;
        }
        if (newPosition.y < 0)
        {
            newPosition.y = settings.screenHeight - settings.partSize;
        }
        else if (newPosition.y >= settings.screenHeight)
        {
            newPosition.y = 0;
        }

        head->SetPosition(newPosition);
    }

    void Snake::MoveBody()
    {
        // Массив для хранения счетчиков поворотов для каждого сегмента
        static std::vector<int> turnCounters(segments.size(), 0);

        if (turnCounters.size() != segments.size())
        {
            turnCounters.resize(segments.size(), 0);
        }

        // Создаем массив для отслеживания, какие сегменты уже обработали текущую точку поворота
        static std::vector<std::vector<bool>> processedTurns(segments.size(), std::vector<bool>(turnPositions.size(), false));

        if (processedTurns.size() != segments.size() ||
            (processedTurns.empty() == false &&
                turnPositions.empty() == false &&
                processedTurns[0].size() != turnPositions.size()))
        {
            processedTurns.resize(segments.size(), std::vector<bool>(turnPositions.size(), false));

            for (auto& row : processedTurns)
            {
                row.resize(turnPositions.size(), false);
            }
        }

        MoveSegments(processedTurns, turnCounters);

        head->SetTexture(head->direction, bodyAssets);
    }

    void Snake::MoveSegments(static std::vector<std::vector<bool>>& processedTurns, static std::vector<int>& turnCounters)
    {
        for (size_t i = 1; i < segments.size(); i++)
        {
            segments[i]->FollowPreviousSegment();

            for (size_t turnIndex = 0; turnIndex < turnPositions.size(); turnIndex++)
            {
                // Если этот сегмент уже обработал эту точку поворота, пропускаем
                if (processedTurns[i][turnIndex])
                {
                    continue;
                }

                Math::Position turnPosition = turnPositions[turnIndex].position;

                if (IsAtTurnPoint(segments[i]->position, turnPosition))
                {
                    segments[i]->previousDirection = segments[i]->direction;
                    Snake_Direction::Direction newDirection = turnPositions[turnIndex].direction;

                    segments[i]->isTurn = true;
                    turnCounters[i] = 0;
                    segments[i]->direction = newDirection;
                    segments[i]->position = turnPosition;
                    processedTurns[i][turnIndex] = true;

                    // Если это последний сегмент тела и он обработал самую первую точку поворота,
                    // удаляем эту точку и обновляем массив processedTurns
                    if (i == segments.size() - 1 && turnIndex == 0)
                    {
                        turnPositions.pop_front();

                        // Сдвигаем все отметки об обработанных поворотах влево
                        for (auto segIndex = 0; segIndex < processedTurns.size(); segIndex++)
                        {
                            for (auto tIndex = 0; tIndex < processedTurns[segIndex].size() - 1; tIndex++)
                            {
                                processedTurns[segIndex][tIndex] = processedTurns[segIndex][tIndex + 1];
                            }

                            if (processedTurns[segIndex].empty() == false)
                            {
                                processedTurns[segIndex].back() = false;
                            }
                        }
                    }

                    break;
                }
            }

            segments[i]->SetTexture(segments[i]->direction, bodyAssets);
            segments[i]->UpdateSpritePosition();

            if (segments[i]->isTurn)
            {
                turnCounters[i]++;

                if (turnCounters[i] >= Settings::SNAKE_TURNS_COUNTER_VALUE)
                {
                    segments[i]->isTurn = false;
                    turnCounters[i] = 0;
                }
            }
        }
    }

    void Snake::SegmentStep(std::shared_ptr < Snake_Segment::Segment> segment, Snake_Direction::Direction setDirection)
    {
        float step = settings.partSize;

        switch (setDirection)
        {
        case Snake_Direction::Direction::Up:
            segment->position.y -= step;
            break;
        case Snake_Direction::Direction::Down:
            segment->position.y += step;
            break;
        case Snake_Direction::Direction::Left:
            segment->position.x -= step;
            break;
        case Snake_Direction::Direction::Right:
            segment->position.x += step;
            break;
        }

        segment->UpdateSpritePosition();
    }

    bool Snake::IsAtTurnPoint(Math::Position segmentPosition, Math::Position turnPosition)
    {
        // Порог для более надежного определения точки поворота
        const float epsilon = settings.partSize * 0.15f;

        float distance = GetDistance(segmentPosition, turnPosition);

        // Если расстояние меньше порога, считаем, что сегмент достиг точки поворота
        return distance <= epsilon;
    }

    float Snake::GetDistance(Math::Position p1, Math::Position p2)
    {
        float dx = p1.x - p2.x;
        float dy = p1.y - p2.y;

        return std::sqrt(dx * dx + dy * dy);
    }

    bool Snake::CanAddTurnPoint(const Math::Position& position)
    {
        // Если список точек поворота пуст, всегда можно добавить новую точку
        if (turnPositions.empty())
        {
            return true;
        }

        const auto& lastTurn = turnPositions.back();
        float distance = GetDistance(position, lastTurn.position);

        // Увеличиваем минимальное расстояние между точками поворота
        // чтобы избежать проблем с близкими точками поворота
        float minDistance = settings.partSize * 1.2f;

        // Возвращаем true, если расстояние достаточно большое
        return distance >= minDistance;
    }

    void Snake::UpdateSegmentsTexture(Views::SnakeBodyViews bodyAssets)
    {
        for (size_t i = 0; i < segments.size(); i++)
        {
            segments[i]->SetTexture(segments[i]->direction, bodyAssets);
        }
    }

    void Snake::AddSegment()
    {
        auto lastSegment = segments.back();
        lastSegment->isTail = false;

        auto segmentGap = (settings.partSize * 0.95f);

        Math::Position newPos;
        sf::Texture newTexture;

        if (lastSegment->direction == Snake_Direction::Direction::Down || lastSegment->direction == Snake_Direction::Direction::Up)
        {
            newPos = { lastSegment->position.x, lastSegment->position.y + segmentGap };

            if (lastSegment->direction == Snake_Direction::Direction::Down)
            {
                newTexture = bodyAssets.tail.down;
            }
            else
            {
                newTexture = bodyAssets.tail.up;
            }
        }
        else
        {
            newPos = { lastSegment->position.x + segmentGap, lastSegment->position.y };
            if (lastSegment->direction == Snake_Direction::Direction::Left)
            {
                newTexture = bodyAssets.tail.left;
            }
            else
            {
                newTexture = bodyAssets.tail.right;
            }
        }

        auto segment = InitSegment(newTexture, newPos);
        segment->isTail = true;
        segment->previousPosition = segment->position;
        segment->direction = lastSegment->direction;
        segment->previousDirection = lastSegment->direction;

        segments.push_back(segment);

        // Увеличиваем счет
        score++;

        if (segments.size() > 1)
        {
            segments.back()->previousSegment = lastSegment;
        }
    }

    bool Snake::CheckCollisions()
    {
        // Проверяем столкновение головы с каждым сегментом тела
        for (size_t i = 1; i < segments.size(); i++)
        {
            if (head->CheckCollision(segments[i]))
            {
                alive = false;

                return true;
            }
        }

        return false;
    }

    bool Snake::CheckCollisions(const Apple::Apple& apple, bool checkOnlyHead)
    {
        if (checkOnlyHead)
        {
            return head->CheckCollision(apple);
        }

        bool result = false;
        for (size_t i = 0; i < segments.size(); i++)
        {
            result |= segments[i]->CheckCollision(apple);
        }

        return result;
    }

    void Snake::Draw(sf::RenderWindow& window)
    {
        // Рисуем сегменты в обратном порядке (сначала хвост, затем тело, в конце голова)
        for (int i = static_cast<int>(segments.size()) - 1; i >= 0; i--)
        {
            window.draw(segments[i]->sprite);
        }
    }

    void Snake::SetDirection(Snake_Direction::Direction setDirection, Apple::Apple& apple)
    {
        if (setDirection == head->direction)
        {
            return;
        }

        head->previousDirection = head->direction;

        if (CanAddTurnPoint(head->position))
        {
            Turn turnPoint;

            turnPoint.position = head->position;
            turnPoint.direction = setDirection;

            turnPositions.push_back(turnPoint);

            // Установим флаг поворота для головы
            head->isTurn = true;
            head->direction = setDirection;
            head->SetTexture(head->direction, bodyAssets);

            MoveSnake(apple);
        }
        else
        {
            // Если не можем добавить точку поворота сейчас (слишком близко к предыдущей),
            // установим флаг ожидания поворота
            pendingDirectionChange = true;
            pendingDirection = setDirection;
        }
    }
}
