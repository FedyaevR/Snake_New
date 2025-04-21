#include "Snake.h"
#include "Math.h"
#include <iostream>
#include <cmath>

// Структура для хранения точек поворота
struct TurnPoint {
    Math::Position position;
    Snake_Direction::Direction direction;
};

namespace Snake
{
    void Snake::Initialize(Settings::Settings settings)
    {
        // Сохраняем настройки
        this->settings = settings;
        deltaTime = settings.deltaTime;
        turnPositions.clear();
        segments.clear();


        // Инициализация головы
        InitSegment(settings, true);

        // Инициализация тела
        for (size_t i = 0; i < Settings::SNAKE_INIT_BODY_PART_COUNT; i++)
        {
            InitSegment(settings);
        }

        // Инициализация хвоста
        InitSegment(settings, false, true);

        // Сохраняем указатель на голову для быстрого доступа
        this->head = &segments[0];
        
        // Связываем сегменты между собой
        for (size_t i = 1; i < segments.size(); i++) 
        {
            segments[i].previousSegment = &segments[i-1];
        }

        // Обновляем текстуры сегментов
        for (auto& segment : segments) 
        {
            segment.SetTexture(segment.direction, bodyAssets);
        }
        
        // Сбрасываем счет и статус
        score = 0;
        alive = true;
        accumulator = 0.0f;
    }

    void Snake::InitSegment(Settings::Settings settings, bool isHead, bool isTail)
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
        segment.isHead = isHead;
        segment.isTail = isTail;
        segment.previousPosition = segment.position;
        segment.direction = Snake_Direction::Direction::Up;
        segment.previousDirection = Snake_Direction::Direction::Up;

        segments.push_back(segment);
    }

    Snake_Segment::Segment Snake::InitSegment(sf::Texture texture, Math::Position position)
    {
        auto segment = Snake_Segment::Segment();

        segment.texture = texture;
        segment.position = position;
        segment.previousPosition = position;
        segment.direction = Snake_Direction::Direction::Up;
        segment.previousDirection = Snake_Direction::Direction::Up;

        segment.sprite.setTexture(segment.texture);
        segment.sprite.setOrigin(Math::GetItemOrigin(segment.sprite, { 0.5f, 0.5f }));
        segment.sprite.setScale(Math::GetSpriteScale(segment.sprite, { settings.partSize, settings.partSize }));
        segment.UpdateSpritePosition();

        return segment;
    }

    void Snake::Update(float deltaTime)
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
        
        MoveSnake();
    }

    void Snake::MoveSnake()
    {
        head->previousPosition = head->position;
        
        MoveHead();
        MoveBody();
        CheckCollisions();
        
        for (auto& segment : segments)
        {
            segment.SetTexture(segment.direction, bodyAssets);
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

        // Проблема в том, что сегмент меджу двумя точками поворота помечается как поворот. Если два поворота, разделяет один сегмент
        for (size_t i = 1; i < segments.size(); i++)
        {
            segments[i].FollowPreviousSegment();
            
            for (size_t turnIndex = 0; turnIndex < turnPositions.size(); turnIndex++)
            {
                // Если этот сегмент уже обработал эту точку поворота, пропускаем
                if (processedTurns[i][turnIndex])
                {
                    continue;
                }

                Math::Position turnPos = turnPositions[turnIndex].position;
                std::cout << "Size of turn positions: " << turnPositions.size() << "\n";
                

                if (IsAtTurnPoint(segments[i].position, turnPos) == false)
                {
                    std::cout << "Segment: " << i << " is not a turn point. Point: x:" << segments[i].position.x << " Y: " << segments[i].position.y << " Turn pos is: x:" << turnPos.x << " y: " << turnPos.y << " Turn index: " << turnIndex << "\n";
                }

                if (IsAtTurnPoint(segments[i].position, turnPos))
                {
                    std::cout << "Is at turn point: x:" << segments[i].position.x << " y: " << segments[i].position.y << " segment index: " << i << " turn: " << turnIndex << "\n";
                    
                    segments[i].previousDirection = segments[i].direction;
                    Snake_Direction::Direction newDirection = turnPositions[turnIndex].direction;

                    segments[i].isTurn = true;
                    turnCounters[i] = 0; 
                    segments[i].direction = newDirection;
                    segments[i].position = turnPos;
                    processedTurns[i][turnIndex] = true;
                    
                    // Если это последний сегмент тела и он обработал самую первую точку поворота,
                    // удаляем эту точку и обновляем массив processedTurns
                    if (i == segments.size() - 1 && turnIndex == 0)
                    {
                        turnPositions.pop_front();
                        
                        // Сдвигаем все отметки об обработанных поворотах влево
                        for (size_t segIndex = 0; segIndex < processedTurns.size(); segIndex++)
                        {
                            for (size_t tIndex = 0; tIndex < processedTurns[segIndex].size() - 1; tIndex++)
                            {
                                processedTurns[segIndex][tIndex] = processedTurns[segIndex][tIndex + 1];
                            }

                            if (!processedTurns[segIndex].empty())
                            {
                                processedTurns[segIndex].back() = false;
                            }
                        }
                    }

                    break;
                }
            }

            segments[i].SetTexture(segments[i].direction, bodyAssets);
            
            // Обновляем позицию спрайта
            segments[i].UpdateSpritePosition();
            
            // Увеличиваем счетчик поворота и сбрасываем флаг после определенного количества шагов
            if (segments[i].isTurn)
            {
                turnCounters[i]++;
                if (turnCounters[i] >= 3) // Увеличиваем до 3 для более плавного поворота
                {
                    segments[i].isTurn = false;
                    turnCounters[i] = 0;
                }
            }
        }
        
        // Обновляем текстуру головы
        head->SetTexture(head->direction, bodyAssets);
        
        // Дополнительная проверка для предотвращения "залипания" поворотов
        for (size_t i = 1; i < segments.size() - 1; i++)
        {
            // Если сегмент в состоянии поворота, но его направление совпадает с соседними сегментами,
            // сбрасываем флаг поворота - это уже не реальный поворот
            if (segments[i].isTurn && 
                segments[i].direction == segments[i-1].direction &&
                segments[i].direction == segments[i+1].direction)
            {
                segments[i].isTurn = false;
            }
        }
    }

    void Snake::SegmentStep(Snake_Segment::Segment& segment, Snake_Direction::Direction setDirection)
    {
        float step = settings.partSize;
        
        // Перемещаем сегмент в заданном направлении
        switch (setDirection)
        {
            case Snake_Direction::Direction::Up:
                segment.position.y -= step;
                break;
            case Snake_Direction::Direction::Down:
                segment.position.y += step;
                break;
            case Snake_Direction::Direction::Left:
                segment.position.x -= step;
                break;
            case Snake_Direction::Direction::Right:
                segment.position.x += step;
                break;
        }
        
        // Обновляем позицию спрайта
        segment.UpdateSpritePosition();
    }

    bool Snake::IsAtTurnPoint(Math::Position segmentPosition, Math::Position turnPosition)
    {
        // Увеличиваем порог для более надежного определения точки поворота
        const float epsilon = settings.partSize * 0.15f;
        
        // Вычисляем точное расстояние между позициями
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
        
        // Проверяем расстояние до последней добавленной точки поворота
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
        // Обновляем текстуры для всех сегментов
        for (size_t i = 0; i < segments.size(); i++)
        {
            segments[i].SetTexture(segments[i].direction, bodyAssets);
        }
    }

    void Snake::AddSegment()
    {
        // Получаем последний сегмент (текущий хвост)
        auto& lastSegment = segments.back();
        lastSegment.isTail = false; // Убираем флаг хвоста с последнего сегмента
        
        // Создаем новый сегмент (новый хвост)
        auto newSegment = Snake_Segment::Segment();
        newSegment.isTail = true; // Устанавливаем флаг хвоста
        
        // Устанавливаем позицию нового сегмента равной позиции предыдущего хвоста
        newSegment.position = lastSegment.position;
        newSegment.previousPosition = lastSegment.previousPosition;
        newSegment.direction = lastSegment.direction;
        newSegment.previousDirection = lastSegment.previousDirection;
        
        // Устанавливаем текстуру для хвоста
        if (lastSegment.direction == Snake_Direction::Direction::Up)
            newSegment.texture = bodyAssets.tail.down; // Хвост смотрит вниз при движении вверх
        else if (lastSegment.direction == Snake_Direction::Direction::Down)
            newSegment.texture = bodyAssets.tail.up; // Хвост смотрит вверх при движении вниз
        else if (lastSegment.direction == Snake_Direction::Direction::Left)
            newSegment.texture = bodyAssets.tail.right; // Хвост смотрит вправо при движении влево
        else
            newSegment.texture = bodyAssets.tail.left; // Хвост смотрит влево при движении вправо
            
        newSegment.sprite.setTexture(newSegment.texture);
        newSegment.sprite.setOrigin(Math::GetItemOrigin(newSegment.sprite, { 0.5f, 0.5f }));
        newSegment.sprite.setScale(Math::GetSpriteScale(newSegment.sprite, { settings.partSize, settings.partSize }));
        newSegment.UpdateSpritePosition();
        
        // Устанавливаем связь с предыдущим сегментом
        newSegment.previousSegment = &segments.back();
        
        // Добавляем новый сегмент в вектор
        segments.push_back(newSegment);
        
        // Увеличиваем счет
        score++;
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

    void Snake::Draw(sf::RenderWindow& window)
    {
        // Рисуем сегменты в обратном порядке (сначала хвост, затем тело, в конце голова)
        for (int i = static_cast<int>(segments.size()) - 1; i >= 0; i--)
        {
            window.draw(segments[i].sprite);
        }
    }

    void Snake::SetDirection(Snake_Direction::Direction setDirection)
    {
        // Игнорируем изменение направления, если змейка мертва
        if (!alive) return;
        
        // Проверяем, является ли новое направление противоположным текущему направлению
        // (предотвращаем разворот на 180 градусов)
        if ((setDirection == Snake_Direction::Direction::Up && head->direction == Snake_Direction::Direction::Down) ||
            (setDirection == Snake_Direction::Direction::Down && head->direction == Snake_Direction::Direction::Up) ||
            (setDirection == Snake_Direction::Direction::Left && head->direction == Snake_Direction::Direction::Right) ||
            (setDirection == Snake_Direction::Direction::Right && head->direction == Snake_Direction::Direction::Left))
        {
            return; // Игнорируем противоположное направление
        }
        
        // Если новое направление совпадает с текущим, ничего не делаем
        if (setDirection == head->direction)
        {
            return;
        }
        
        // Запоминаем предыдущее направление головы до изменения
        head->previousDirection = head->direction;
        
        // Проверяем, можно ли добавить точку поворота
        if (CanAddTurnPoint(head->position))
        {
            // Создаём структуру для новой точки поворота
            Turn turnPoint;
            
            // Используем ТЕКУЩУЮ позицию головы (до смещения)
            turnPoint.position = head->position;
            turnPoint.direction = setDirection;
            
            // Добавляем точку поворота в список
            turnPositions.push_back(turnPoint);
            
            // Установим флаг поворота для головы
            head->isTurn = true;
            
            // Устанавливаем новое направление для головы
            head->direction = setDirection;
            
            // Обновляем текстуру головы немедленно
            head->SetTexture(head->direction, bodyAssets);
            
            // Сразу перемещаем змейку в новом направлении
            MoveSnake();
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
