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

        // Центр экрана
        const float centerX = settings.screenWidth / 2.0f;
        const float centerY = settings.screenHeight / 2.0f;
        
        // Расстояние между сегментами (уменьшенное для лучшего визуального соединения)
        const float segmentGap = settings.partSize * 0.95f;
        
        // Создаем голову в центре экрана
        auto head = InitSegment(bodyAssets.head.up, { centerX, centerY });
        head.isHead = true;
        head.previousPosition = head.position;
        head.direction = Snake_Direction::Direction::Up;
        head.previousDirection = Snake_Direction::Direction::Up;
        
        // Создаем сегменты тела под головой (вниз от головы)
        // Располагаем сегменты с небольшим уменьшенным расстоянием для лучшего визуального соединения
        auto body1 = InitSegment(bodyAssets.body.vertical, {centerX, centerY + segmentGap});
        body1.previousPosition = body1.position;
        body1.direction = Snake_Direction::Direction::Up;
        body1.previousDirection = Snake_Direction::Direction::Up;

        auto body2 = InitSegment(bodyAssets.body.vertical, { centerX, centerY + segmentGap });
        body2.previousPosition = body2.position;
        body2.direction = Snake_Direction::Direction::Up;
        body2.previousDirection = Snake_Direction::Direction::Up;
        
        auto tail = InitSegment(bodyAssets.body.vertical, {centerX, centerY + 2 * segmentGap});
        tail.previousPosition = tail.position;
        tail.direction = Snake_Direction::Direction::Up;
        tail.previousDirection = Snake_Direction::Direction::Up;
        
        // Последний сегмент делаем хвостом
        tail.isTail = true;

        // Добавляем сегменты в вектор
        segments.push_back(head);
        segments.push_back(body1);
        segments.push_back(body2);
        segments.push_back(tail);

        // Сохраняем указатель на голову для быстрого доступа
        this->head = &segments[0];
        
        // Связываем сегменты между собой
        for (size_t i = 1; i < segments.size(); i++) {
            segments[i].previousSegment = &segments[i-1];
        }

        // Обновляем текстуры сегментов
        for (auto& segment : segments) {
            segment.SetTexture(segment.direction, bodyAssets);
        }
        
        // Сбрасываем счет и статус
        score = 0;
        alive = true;
        accumulator = 0.0f;
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
        if (!alive)
        {
            return;
        }
        
        // Аккумулятор для контроля скорости движения
        accumulator += deltaTime;
        if (accumulator < settings.moveSpeed)
        {
            return;
        }
        
        accumulator = 0.0f;
        
        // Счетчик шагов для головы (уменьшаем период поворота до 2 шагов)
        // Судя по всему, это лишнее...
        static int headTurnCounter = 0;
        headTurnCounter = (headTurnCounter + 1) % 2;
        
        // Сохраняем предыдущую позицию головы
        head->previousPosition = head->position;
        
        // Перемещаем голову
        MoveHead();
        
        // Перемещаем тело
        MoveBody();
        
        // Проверяем столкновения
        CheckCollisions();
        
        // Обновляем текстуры всех сегментов
        for (auto& segment : segments)
        {
            segment.SetTexture(segment.direction, bodyAssets);
        }
    }

    void Snake::MoveHead()
    {
        // Вычисляем новую позицию головы в зависимости от направления
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

        // Проверяем границы экрана и при необходимости переносим голову на противоположную сторону
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
        
        // Устанавливаем новую позицию головы
        head->SetPosition(newPosition);
    }

    void Snake::MoveBody()
    {
        // Массив для хранения счетчиков поворотов для каждого сегмента
        static std::vector<int> turnCounters(segments.size(), 0);
        
        // Если размеры изменились, обновляем массив
        if (turnCounters.size() != segments.size())
        {
            turnCounters.resize(segments.size(), 0);
        }
        
        // Перемещаем каждый сегмент тела, начиная со второго (после головы)
        for (size_t i = 1; i < segments.size(); i++)
        {
            // Проверяем, достиг ли сегмент точки поворота
            if (!turnPositions.empty())
            {
                Math::Position turnPos = turnPositions.front().position;
                
                // Если сегмент достиг точки поворота с достаточной точностью
                if (IsAtTurnPoint(segments[i].position, turnPos))
                {
                    // Сохраняем предыдущее направление
                    segments[i].previousDirection = segments[i].direction;
                    
                    // Устанавливаем новое направление из точки поворота
                    Snake_Direction::Direction newDirection = turnPositions.front().direction;
                    
                    // Отмечаем сегмент как совершающий поворот
                    segments[i].isTurn = true;
                    turnCounters[i] = 0; // Сбрасываем счетчик для этого сегмента
                    
                    // Устанавливаем новое направление
                    segments[i].direction = newDirection;
                    
                    // Устанавливаем позицию точно в точке поворота для избежания смещений
                    segments[i].position = turnPos;
                    
                    // Если это последний сегмент тела, удаляем точку поворота
                    if (i == segments.size() - 1) {
                        turnPositions.pop_front();
                    }
                }
            }
            // Обновляем текстуру сегмента
            segments[i].SetTexture(segments[i].direction, bodyAssets);
            
            // Перемещаем сегмент следуя за предыдущим сегментом
            segments[i].FollowPreviousSegment();
            
            // Обновляем позицию спрайта
            segments[i].UpdateSpritePosition();
            
            // Увеличиваем счетчик поворота и сбрасываем флаг после достаточного количества шагов
            if (segments[i].isTurn)
            {
                turnCounters[i]++;
                // Уменьшаем период до 2 шагов для более быстрого отклика
                if (turnCounters[i] >= 2)
                {
                    segments[i].isTurn = false;
                    turnCounters[i] = 0;
                }
            }
        }
        
        // Обновляем текстуру головы
        head->SetTexture(head->direction, bodyAssets);
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
        // Используем меньший порог для точного определения точки поворота
        // Это уменьшит запаздывание при определении поворота
        const float epsilon = settings.partSize * 0.05f;
        
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
        // Проверяем расстояние до существующих точек поворота
        for (const auto& turnPoint : turnPositions)
        {
            // Вычисляем расстояние между точками
            float distanceX = std::abs(position.x - turnPoint.position.x);
            float distanceY = std::abs(position.y - turnPoint.position.y);
            
            // Если расстояние слишком маленькое, отклоняем новую точку поворота
            if (distanceX < minTurnDistance && distanceY < minTurnDistance)
            {
                return false;
            }
        }
        
        // Если нет близких точек поворота, можно добавить новую
        return true;
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
        // Добавляем новый сегмент в конец змейки
        if (segments.empty()) return;
        
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
        
        // Создаём новую точку поворота, если возможно
        if (CanAddTurnPoint(head->position))
        {
            // Создаём структуру для новой точки поворота
            Turn turnPoint;
            
            // Используем точную позицию головы - без модификаций
            turnPoint.position = head->position;
            turnPoint.direction = setDirection;
            
            // Добавляем точку поворота в список
            turnPositions.push_back(turnPoint);
            
            // Запоминаем предыдущее направление головы до изменения
            head->previousDirection = head->direction;
            
            // Установим флаг поворота для головы
            head->isTurn = true;
            
            // Устанавливаем новое направление для головы
            head->direction = setDirection;
            
            // Обновляем текстуру головы немедленно
            head->SetTexture(head->direction, bodyAssets);
        }
    }
}
